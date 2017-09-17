     * this on Win32, though, since we haven't fork()'d.
     */
    r->server->error_log = stderr;
#endif

#ifdef RLIMIT_CPU
    if (conf->limit_cpu != NULL)
	if ((setrlimit(RLIMIT_CPU, conf->limit_cpu)) != 0)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			"setrlimit: failed to set CPU usage limit");
#endif
#ifdef RLIMIT_NPROC
    if (conf->limit_nproc != NULL)
	if ((setrlimit(RLIMIT_NPROC, conf->limit_nproc)) != 0)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			"setrlimit: failed to set process limit");
#endif
#if defined(RLIMIT_AS)
    if (conf->limit_mem != NULL)
	if ((setrlimit(RLIMIT_AS, conf->limit_mem)) != 0)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			"setrlimit(RLIMIT_AS): failed to set memory usage limit");
#elif defined(RLIMIT_DATA)
    if (conf->limit_mem != NULL)
	if ((setrlimit(RLIMIT_DATA, conf->limit_mem)) != 0)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			"setrlimit(RLIMIT_DATA): failed to set memory usage limit");
#elif defined(RLIMIT_VMEM)
    if (conf->limit_mem != NULL)
	if ((setrlimit(RLIMIT_VMEM, conf->limit_mem)) != 0)
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			"setrlimit(RLIMIT_VMEM): failed to set memory usage limit");
#endif

#ifdef __EMX__
    {
	/* Additions by Alec Kloss, to allow exec'ing of scripts under OS/2 */
	int is_script;
	char interpreter[2048];	/* hope this is large enough for the interpreter path */
	FILE *program;
	program = fopen(r->filename, "rt");
	if (!program) {
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server, "fopen(%s) failed",
			r->filename);
	    return (pid);
	}
	fgets(interpreter, sizeof(interpreter), program);
	fclose(program);
	if (!strncmp(interpreter, "#!", 2)) {
	    is_script = 1;
