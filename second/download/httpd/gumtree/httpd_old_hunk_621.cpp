#define APLOG_NOERRNO		(APLOG_LEVELMASK + 1)

/* Use APLOG_TOCLIENT on ap_log_rerror() to give content
 * handlers the option of including the error text in the 
 * ErrorDocument sent back to the client. Setting APLOG_TOCLIENT
 * will cause the error text to be saved in the request_rec->notes 
 * table, keyed to the string "error-notes", iff:
 * - the severity level of the message is APLOG_WARNING or greater
 * - there are no other "error-notes" set in request_rec->notes
 * Once error-notes is set, it is up to the content handler to
 * determine whether this text should be send back to the client.
 * Note: Client generated text streams sent back to the  client MUST 
 * be escaped to prevent CSS attacks.
 */
#define APLOG_TOCLIENT          (APLOG_LEVELMASK + 2)

/* normal but significant condition on startup, usually printed to stderr */
#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4) 

#ifndef DEFAULT_LOGLEVEL
#define DEFAULT_LOGLEVEL	APLOG_WARNING
