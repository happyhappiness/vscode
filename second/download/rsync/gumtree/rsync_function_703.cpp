static int execCommand(poptContext con)
    /*@*/
{
    poptItem item = con->doExec;
    const char ** argv;
    int argc = 0;
    int rc;

    if (item == NULL) /*XXX can't happen*/
	return POPT_ERROR_NOARG;

    if (item->argv == NULL || item->argc < 1 ||
	(!con->execAbsolute && strchr(item->argv[0], '/')))
	    return POPT_ERROR_NOARG;

    argv = malloc(sizeof(*argv) *
			(6 + item->argc + con->numLeftovers + con->finalArgvCount));
    if (argv == NULL) return POPT_ERROR_MALLOC;	/* XXX can't happen */

    if (!strchr(item->argv[0], '/') && con->execPath) {
	char *s = alloca(strlen(con->execPath) + strlen(item->argv[0]) + sizeof("/"));
	sprintf(s, "%s/%s", con->execPath, item->argv[0]);
	argv[argc] = s;
    } else {
	argv[argc] = findProgramPath(item->argv[0]);
    }
    if (argv[argc++] == NULL) return POPT_ERROR_NOARG;

    if (item->argc > 1) {
	memcpy(argv + argc, item->argv + 1, sizeof(*argv) * (item->argc - 1));
	argc += (item->argc - 1);
    }

    if (con->finalArgv != NULL && con->finalArgvCount > 0) {
	memcpy(argv + argc, con->finalArgv,
		sizeof(*argv) * con->finalArgvCount);
	argc += con->finalArgvCount;
    }

    if (con->leftovers != NULL && con->numLeftovers > 0) {
#if 0
	argv[argc++] = "--";
#endif
	memcpy(argv + argc, con->leftovers, sizeof(*argv) * con->numLeftovers);
	argc += con->numLeftovers;
    }

    argv[argc] = NULL;

#ifdef __hpux
    rc = setresuid(getuid(), getuid(),-1);
    if (rc) return POPT_ERROR_ERRNO;
#else
/*
 * XXX " ... on BSD systems setuid() should be preferred over setreuid()"
 * XXX 	sez' Timur Bakeyev <mc@bat.ru>
 * XXX	from Norbert Warmuth <nwarmuth@privat.circular.de>
 */
#if defined(HAVE_SETUID)
    rc = setuid(getuid());
    if (rc) return POPT_ERROR_ERRNO;
#elif defined (HAVE_SETREUID)
    rc = setreuid(getuid(), getuid()); /*hlauer: not portable to hpux9.01 */
    if (rc) return POPT_ERROR_ERRNO;
#else
    ; /* Can't drop privileges */
#endif
#endif

    if (argv[0] == NULL)
	return POPT_ERROR_NOARG;
#ifdef MYDEBUG
    {	const char ** avp;
	fprintf(stderr, "==> execvp(%s) argv[%d]:", argv[0], argc);
	for (avp = argv; *avp; avp++)
	    fprintf(stderr, " '%s'", *avp);
	fprintf(stderr, "\n");
    }
#endif

    rc = execvp(argv[0], (char *const *)argv);
    return POPT_ERROR_ERRNO;
}