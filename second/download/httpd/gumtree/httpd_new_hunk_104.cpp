    else {
	syslog(level & APLOG_LEVELMASK, "%s", errstr);
    }
#endif
}
    
API_EXPORT(void) ap_log_error (const char *file, int line, int level,
			      const server_rec *s, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, s, NULL, fmt, args);
    va_end(args);
}

API_EXPORT(void) ap_log_rerror(const char *file, int line, int level,
			       const request_rec *r, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, r->server, r, fmt, args);
    if (ap_table_get(r->notes, "error-notes") == NULL) {
	char errstr[MAX_STRING_LEN];

	ap_vsnprintf(errstr, sizeof(errstr), fmt, args);
	ap_table_set(r->notes, "error-notes", errstr);
    }
    va_end(args);
}

void ap_log_pid (pool *p, char *fname)
{
    FILE *pid_file;
    struct stat finfo;
    static pid_t saved_pid = -1;
    pid_t mypid;

    if (!fname) return;

    fname = ap_server_root_relative (p, fname);
    mypid = getpid();
    if (mypid != saved_pid && stat(fname,&finfo) == 0) {
      /* USR1 and HUP call this on each restart.
       * Only warn on first time through for this pid.
       *
       * XXX: Could just write first time through too, although
       *      that may screw up scripts written to do something
       *      based on the last modification time of the pid file.
       */
      ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, NULL,
		   ap_psprintf(p,
			       "pid file %s overwritten -- Unclean shutdown of previous apache run?",
			       fname)
		   );
    }

    if(!(pid_file = fopen(fname,"w"))) {
	perror("fopen");
        fprintf(stderr,"httpd: could not log pid to file %s\n", fname);
        exit(1);
    }
    fprintf(pid_file,"%ld\n",(long)mypid);
    fclose(pid_file);
    saved_pid = mypid;
}

API_EXPORT(void) ap_log_error_old (const char *err, server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, s, "%s", err);
}

API_EXPORT(void) ap_log_unixerr (const char *routine, const char *file,
			      const char *msg, server_rec *s)
{
    ap_log_error(file, 0, APLOG_ERR, s, "%s", msg);
}

API_EXPORT(void) ap_log_printf (const server_rec *s, const char *fmt, ...)
{
    va_list args;
    
    va_start(args, fmt);
    log_error_core(APLOG_MARK, APLOG_ERR, s, NULL, fmt, args);
    va_end(args);
}

API_EXPORT(void) ap_log_reason (const char *reason, const char *file, request_rec *r) 
{
    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
