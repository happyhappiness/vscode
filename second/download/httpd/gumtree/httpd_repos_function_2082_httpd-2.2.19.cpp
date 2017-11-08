static apr_status_t ap_unix_create_privileged_process(
                              apr_proc_t *newproc, const char *progname,
                              const char * const *args,
                              const char * const *env,
                              apr_procattr_t *attr, ap_unix_identity_t *ugid,
                              apr_pool_t *p)
{
    int i = 0;
    const char **newargs;
    char *newprogname;
    char *execuser, *execgroup;
    const char *argv0;

    if (!unixd_config.suexec_enabled) {
        return apr_proc_create(newproc, progname, args, env, attr, p);
    }

    argv0 = ap_strrchr_c(progname, '/');
    /* Allow suexec's "/" check to succeed */
    if (argv0 != NULL) {
        argv0++;
    }
    else {
        argv0 = progname;
    }


    if (ugid->userdir) {
        execuser = apr_psprintf(p, "~%ld", (long) ugid->uid);
    }
    else {
        execuser = apr_psprintf(p, "%ld", (long) ugid->uid);
    }
    execgroup = apr_psprintf(p, "%ld", (long) ugid->gid);

    if (!execuser || !execgroup) {
        return APR_ENOMEM;
    }

    i = 0;
    if (args) {
        while (args[i]) {
            i++;
            }
    }
    /* allocate space for 4 new args, the input args, and a null terminator */
    newargs = apr_palloc(p, sizeof(char *) * (i + 4));
    newprogname = SUEXEC_BIN;
    newargs[0] = SUEXEC_BIN;
    newargs[1] = execuser;
    newargs[2] = execgroup;
    newargs[3] = apr_pstrdup(p, argv0);

    /*
    ** using a shell to execute suexec makes no sense thus
    ** we force everything to be APR_PROGRAM, and never
    ** APR_SHELLCMD
    */
    if(apr_procattr_cmdtype_set(attr, APR_PROGRAM) != APR_SUCCESS) {
        return APR_EGENERAL;
    }

    i = 1;
    do {
        newargs[i + 3] = args[i];
    } while (args[i++]);

    return apr_proc_create(newproc, newprogname, newargs, env, attr, p);
}