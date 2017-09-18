    RAISE_SIGSTOP(CGI_CHILD);
#ifdef DEBUG_CGI
    fprintf(dbg, "Attempting to exec %s as CGI child (argv0 = %s)\n",
            r->filename, argv[0]);
#endif

    if (e_info->prog_type == RUN_AS_CGI) {
        ap_add_cgi_vars(r);
    }
    else /* SSIs want a controlled environment and a special path. */
    {
        add_ssi_vars(r, e_info->next);
    }
    env = (const char * const *)ap_create_environment(p, r->subprocess_env);

#ifdef DEBUG_CGI
    fprintf(dbg, "Environment: \n");
    for (i = 0; env[i]; ++i)
        fprintf(dbg, "'%s'\n", env[i]);
