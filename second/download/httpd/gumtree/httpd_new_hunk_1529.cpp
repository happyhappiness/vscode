			 "setrlimit(RLIMIT_VMEM): failed to set memory "
			 "usage limit");
	}
    }
#endif

#ifdef OS2
    {
	/* Additions by Alec Kloss, to allow exec'ing of scripts under OS/2 */
	int is_script;
	char interpreter[2048];	/* hope it's enough for the interpreter path */
	FILE *program;

	program = fopen(r->filename, "rt");
	if (!program) {
	    ap_log_rerror(APLOG_MARK, APLOG_ERR, r, "fopen(%s) failed",
			 r->filename);
	    return (pid);
	}
	fgets(interpreter, sizeof(interpreter), program);
	fclose(program);
	if (!strncmp(interpreter, "#!", 2)) {
