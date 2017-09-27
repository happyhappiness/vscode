
/* APLOG_NOERRNO is ignored and should not be used.  It will be
 * removed in a future release of Apache.
 */
#define APLOG_NOERRNO		(APLOG_LEVELMASK + 1)

/* Use APLOG_TOCLIENT on ap_log_rerror() to give content
 * handlers the option of including the error text in the 
 * ErrorDocument sent back to the client. Setting APLOG_TOCLIENT
 * will cause the error text to be saved in the request_rec->notes 
 * table, keyed to the string "error-notes", if and only if:
 * - the severity level of the message is APLOG_WARNING or greater
 * - there are no other "error-notes" set in request_rec->notes
 * Once error-notes is set, it is up to the content handler to
 * determine whether this text should be sent back to the client.
 * Note: Client generated text streams sent back to the client MUST 
 * be escaped to prevent CSS attacks.
 */
#define APLOG_TOCLIENT          ((APLOG_LEVELMASK + 1) * 2)

/* normal but significant condition on startup, usually printed to stderr */
#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4) 

#ifndef DEFAULT_LOGLEVEL
#define DEFAULT_LOGLEVEL	APLOG_WARNING
#endif

#define APLOG_NO_MODULE         -1

/*
 * Objects with static storage duration are set to NULL if not
 * initialized explicitly. This means if aplog_module_index
 * is not initalized using the APLOG_USE_MODULE or the
 * AP_DECLARE_MODULE macro, we can safely fall back to
 * use APLOG_NO_MODULE.
 */
static int * const aplog_module_index;
#define APLOG_MODULE_INDEX  \
    (aplog_module_index ? *aplog_module_index : APLOG_NO_MODULE)

/*
 * APLOG_MAX_LOGLEVEL can be used to remove logging above some
 * specified level at compile time.
 */
#ifndef APLOG_MAX_LOGLEVEL
#define APLOG_MODULE_IS_LEVEL(s,module_index,level)              \
          ( (((level)&APLOG_LEVELMASK) <= APLOG_NOTICE) ||       \
            (s == NULL) ||                                       \
            (ap_get_server_module_loglevel(s, module_index)      \
             >= ((level)&APLOG_LEVELMASK) ) )
