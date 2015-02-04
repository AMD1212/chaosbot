#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <libconfig.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>

/* argparse options */
const char *argp_program_version = "chaosbot 0.01";
const char *argp_program_bug_address = "<somemail@somehost.tld>";
static char doc[] = "chaosbot - A lightweight irc bot";

static struct argp_option options[] = {
  {"config",  'c', "FILE",      0,  "Use File as config" },
  { 0 }
};

struct arguments {
  char *output_file;
};

/* parse options */
static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  /* get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key) {
    case 'c':
      arguments->output_file = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num != 1)
        /* too many arguments. */
        argp_usage (state);
      //arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num != 0)
        /* not enough arguments. */
        argp_usage (state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

// Declares
static void chaosbot_getConfig(char *config_file_name);
static int chaosbot_connect(void);
static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_channel(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

int main(int argc, char **argv) {
  struct arguments arguments;

  /* default values */
  arguments.output_file = "-";
  /* pars arguments */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  
  //TODO chaosbot_getConfig();
  chaosbot_getConfig(arguments.output_file);
  /* connect */
  chaosbot_connect();
  //TODO choasbot_loadPlugins();
  return EXIT_SUCCESS;
}

static void chaosbot_getConfig(char *config_file_name) {
  /* getting config */
  config_t cfg;
  const char *server, *port, *channel, *name, *rl_name;

  //char *config_file_name = "chaosbot.conf";
 
  /* init */
  config_init(&cfg);

  /* read file, if error exit */
  if (!config_read_file(&cfg, config_file_name)) {
    printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return;
  }
 
  /* get the infos */
  if (!config_lookup_string(&cfg, "server", &server)) {
    printf("No 'server' setting in configuration file.\n");
    exit(EXIT_FAILURE);
  }
  printf("config server:\t%s\n", server);

  if (!config_lookup_string(&cfg, "port", &port)) {
    printf("No 'port' setting in configuration file.\n");
    exit(EXIT_FAILURE);
  }
  printf("config port:\t%s\n", port);

  if (!config_lookup_string(&cfg, "channel", &channel)) {
    printf("No 'channel' setting in configuration file.\n");
    exit(EXIT_FAILURE);
  }
  printf("config channel:\t%s\n", channel);

    if (!config_lookup_string(&cfg, "name", &name)) {
    printf("No 'name' setting in configuration file.\n");
    exit(EXIT_FAILURE);
  }
  printf("config name:\t%s\n", name);

  if (!config_lookup_string(&cfg, "rl_name", &rl_name)) {
    printf("No 'rl_name' setting in configuration file.\n");
    exit(EXIT_FAILURE);
  }
  printf("config rl_name:\t%s\n", rl_name);

  /* clean up */
  config_destroy(&cfg);
}

static int chaosbot_connect() {
	// The IRC callbacks structure
	irc_callbacks_t callbacks;

	// Init it
	memset ( &callbacks, 0, sizeof(callbacks) );

	// Set up the mandatory events
	callbacks.event_connect = event_connect;
	callbacks.event_numeric = event_numeric;

	// Set up the rest of events
	callbacks.event_join = event_join;
	callbacks.event_channel = event_channel;
	callbacks.event_privmsg = event_privmsg;

	// Now create the session
	irc_session_t * session = irc_create_session( &callbacks );

	if ( !session ) {
	    // Handle the error
		printf("Error handling session\n");
		return 1337;
	} else {
		printf("Session created\n");
	}

	// Connect to a regular IRC server
	if ( irc_connect (session, "irc.freenode.net", 6667, 0, "mr_muh", "mr_muh_", "mr_cow" ) ) {
	  // Handle the error: irc_strerror() and irc_errno()
	}

	if (irc_run(session) != 0) {
	  // Either the connection to the server could not be established or terminated. See irc_errno()
		printf("Running\n");
	}


	return 256;
}


// Events
static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	printf("Chaosbot_connect: Event: %s Origin: %s Count: %u\n", event, origin, count);
}

static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count) {
	printf("Numeric: At the moment i do nothing - Event: %u Origin: %s Count: %u\n", event, origin, count);
	if (event == 376) {
			if (irc_cmd_join( session, "#onders.org", 0) ) {
	 			 // most likely connection error
				printf("Error joining channel\n");
			}
	}
}
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	printf("Join: We have joined a channel, lets see what this does\n");
}

static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	//printf("PrivMessage: Event: %s Origin: %s Count: %u\n", event, origin, count);
	printf("PrivMessage: User %s sent a message: %s\n", origin, params[1]);
}

static void event_channel(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	//printf("ChannelMessage: Event: %s Origin: %s Count: %u\n", event, origin, count);
	printf("ChannelMessage: User %s sent a message: %s\n", origin, params[1]);
}
