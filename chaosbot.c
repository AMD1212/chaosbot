#include <argp.h>
#include <stdio.h>
#include <string.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>

/* include config */
#include "config.h"

/* argparse options */
const char *argp_program_version = VERSION;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;
static char doc[] = "chaosbot - a lightweight irc bot";

static struct argp argp = {0, 0, 0, doc, 0, 0, 0};

/* declares */
static int chaosbot_connect(void);
static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_channel(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

int main(int argc, char **argv) {
  /* pars arguments */
  argp_parse (&argp, argc, argv, 0, 0, 0);
  
  /* connect */
  chaosbot_connect();
  //TODO choasbot_loadPlugins();
  return EXIT_SUCCESS;
}

static int chaosbot_connect() {
  /* The IRC callbacks structure */
  irc_callbacks_t callbacks = {
    /* Set up the mandatory events */
    .event_connect = event_connect,
    .event_numeric = event_numeric,

      /* Set up the rest of events */
    .event_join = event_join,
    .event_channel = event_channel,
    .event_privmsg = event_privmsg
  };

  // Now create the session
  irc_session_t * session = irc_create_session( &callbacks );

  if (!session) {
    // Handle the error
    printf("Error handling session\n");
    return 1337;
  } else {
    printf("Session created\n");
  }

  // Connect to a regular IRC server
  if (irc_connect(session, SERVER, PORT, 0, NAME, RES_NAME, REAL_NAME)) {
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
    if (irc_cmd_join(session, CHANNEL, 0)) {
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
