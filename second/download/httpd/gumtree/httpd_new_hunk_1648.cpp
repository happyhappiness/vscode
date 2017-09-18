#if defined(WIN32)
    child_pid = spawnvp(compr[parm->method].argv[0],
			compr[parm->method].argv);
    return (child_pid);
#else
    execvp(compr[parm->method].argv[0], compr[parm->method].argv);
    ap_log_rerror(APLOG_MARK, APLOG_ERR, parm->r,
		MODNAME ": could not execute `%s'.",
		compr[parm->method].argv[0]);
    return -1;
#endif
}

