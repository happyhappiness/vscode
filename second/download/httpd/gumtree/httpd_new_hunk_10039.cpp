#define APLOG_MARK	__FILE__,__LINE__

void ap_open_logs (server_rec *, pool *p);
API_EXPORT(void) ap_log_error(const char *file, int line, int level,
			     const server_rec *s, const char *fmt, ...)
			    __attribute__((format(printf,5,6)));
API_EXPORT(void) ap_log_rerror(const char *file, int line, int level,
			     const request_rec *s, const char *fmt, ...)
			    __attribute__((format(printf,5,6)));
API_EXPORT(void) ap_error_log2stderr (server_rec *);     

void ap_log_pid (pool *p, char *fname);
/* These are for legacy code, new code should use ap_log_error,
 * or ap_log_rerror.
 */
API_EXPORT(void) ap_log_error_old(const char *err, server_rec *s);
API_EXPORT(void) ap_log_unixerr(const char *routine, const char *file,
			     const char *msg, server_rec *s);
API_EXPORT(void) ap_log_printf(const server_rec *s, const char *fmt, ...)
			    __attribute__((format(printf,2,3)));
API_EXPORT(void) ap_log_reason(const char *reason, const char *fname,
++ apache_1.3.2/src/include/http_protocol.h	1998-08-09 22:33:10.000000000 +0800
