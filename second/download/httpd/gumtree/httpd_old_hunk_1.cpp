#define	APLOG_DEBUG	7	/* debug-level messages */

#define	APLOG_LEVELMASK	7	/* mask off the level value */

#endif

#define APLOG_NOERRNO		(APLOG_LEVELMASK + 1)

/* Use APLOG_TOCLIENT to cause ap_log_rerror() to send the message
 * to the client in addition to recording it to the error log.
 */
#define APLOG_TOCLIENT          (APLOG_LEVELMASK + 2)

/* normal but significant condition on startup, usually printed to stderr */
#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4) 

