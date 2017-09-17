    else {
	syslog(level & APLOG_LEVELMASK, "%s", errstr);
    }
#endif
}
    

void ap_log_pid (pool *p, char *fname)
{
    FILE *pid_file;

    if (!fname) return;
    fname = ap_server_root_relative (p, fname);
    if(!(pid_file = fopen(fname,"w"))) {
	perror("fopen");
        fprintf(stderr,"httpd: could not log pid to file %s\n", fname);
        exit(1);
    }
    fprintf(pid_file,"%ld\n",(long)getpid());
    fclose(pid_file);
}

API_EXPORT(void) ap_log_error_old (const char *err, server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, s, err);
}

API_EXPORT(void) ap_log_unixerr (const char *routine, const char *file,
			      const char *msg, server_rec *s)
{
    ap_log_error(file, 0, APLOG_ERR, s, msg);
}

API_EXPORT(void) ap_log_printf (const server_rec *s, const char *fmt, ...)
{
    char buf[MAX_STRING_LEN];
    va_list args;
    
    va_start(args, fmt);
    ap_vsnprintf(buf, sizeof(buf), fmt, args);
    ap_log_error(APLOG_MARK, APLOG_ERR, s, buf);
    va_end(args);
}

API_EXPORT(void) ap_log_reason (const char *reason, const char *file, request_rec *r) 
{
    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
