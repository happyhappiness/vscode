static void execCommand(poptContext con) {
    const char ** argv;
    int pos = 0;
    const char * script = con->doExec->script;

    argv = malloc(sizeof(*argv) *
			(6 + con->numLeftovers + con->finalArgvCount));

    if (!con->execAbsolute && strchr(script, '/')) return;

    if (!strchr(script, '/') && con->execPath) {
	char *s = malloc(strlen(con->execPath) + strlen(script) + 2);
	sprintf(s, "%s/%s", con->execPath, script);
	argv[pos] = s;
    } else {
	argv[pos] = script;
    }
    pos++;

    argv[pos] = findProgramPath(con->os->argv[0]);
    if (argv[pos]) pos++;
    argv[pos++] = ";";

    memcpy(argv + pos, con->finalArgv, sizeof(*argv) * con->finalArgvCount);
    pos += con->finalArgvCount;

    if (con->numLeftovers) {
	argv[pos++] = "--";
	memcpy(argv + pos, con->leftovers, sizeof(*argv) * con->numLeftovers);
	pos += con->numLeftovers;
    }

    argv[pos++] = NULL;

#ifdef __hpux
    setresuid(getuid(), getuid(),-1);
#else
/*
 * XXX " ... on BSD systems setuid() should be preferred over setreuid()"
 * XXX 	sez' Timur Bakeyev <mc@bat.ru>
 * XXX	from Norbert Warmuth <nwarmuth@privat.circular.de>
 */
#if defined(HAVE_SETUID)
    setuid(getuid());
#elif defined (HAVE_SETREUID)
    setreuid(getuid(), getuid()); /*hlauer: not portable to hpux9.01 */
#else
    ; /* Can't drop privileges */
#endif
#endif

    execvp(argv[0], (char *const *)argv);
}