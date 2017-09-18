    RAISE_SIGSTOP(CGI_CHILD);
#ifdef DEBUG_CGI
    fprintf(dbg, "Attempting to exec %s as CGI child (argv0 = %s)\n",
            r->filename, argv[0]);
#endif

    env = (const char * const *)ap_create_environment(p, r->subprocess_env);

#ifdef DEBUG_CGI
    fprintf(dbg, "Environment: \n");
    for (i = 0; env[i]; ++i)
        fprintf(dbg, "'%s'\n", env[i]);
