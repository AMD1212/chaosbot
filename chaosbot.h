#ifndef __CHAOSBOT_H
#define __CHAOSBOT_H

/* Default parameters */
#define DEFAULT_IRC_SERVER "irc.freenode.net"
#define DEFAULT_IRC_PORT 6667
#define DEFAULT_IRC_NICK "ChaosBot-1337-"
#define DEFAULT_IRC_USER "ChaosBot-1337-"
#define DEFAULT_IRC_REALNAME "1337 Bot in C"

/* Printing macros */
#define pr_err(fmt, args...)   fprintf(stderr, "ERROR: " fmt, ## args)
#define pr_warn(fmt, args...)  fprintf(stderr, "WARNING: " fmt, ## args)

/* Prototpyes */
static int chaosbot_connect(void);

/* Event Prototypes */
static void event_connect(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_numeric(irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count);
static void event_join(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_channel(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);
static void event_privmsg(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);

#endif
