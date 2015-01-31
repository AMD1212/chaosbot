#include <stdio.h>
#include <string.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>

// Declares
static int chaosbot_connect(void);
static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);


int main(void) 
{
	chaosbot_connect();
	return 0;
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
	if ( irc_connect (session, "irc.freenode.net", 6667, 0, "ChaosBot-1337-", "ChaosBot-1337-", "1337 Bot in C" ) ) {
	  // Handle the error: irc_strerror() and irc_errno()
	}

	if (irc_run(session) != 0) {
	  // Either the connection to the server could not be established or terminated. See irc_errno()
		printf("Running\n");
	}


	return 256;
}

static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	printf("Connect: At the moment i do nothing\n");
}

static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count) {
	printf("Numeric: At the moment i do nothing - Event: %u Origin: %s Count: %u\n", event, origin, count);
	if (event == 376) {
			if (irc_cmd_join( session, "#chaossbg", 0) ) {
	 			 // most likely connection error
				printf("Error joining channel\n");
			}
	}
}
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	printf("Join: We have joined a channel, lets see what this does");
}

static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count) {
	printf("PrivMessage: looks like you got the following - Event: %s Origin: %s Count: %u\n", event, origin, count);
}
