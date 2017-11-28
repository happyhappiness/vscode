static void WIN32_build_argv(char *cmd)
{
    int argvlen = 0;
    char *word;

    WIN32_argc = 1;
    WIN32_argv = (char **) xmalloc ((WIN32_argc+1) * sizeof (char *));
    WIN32_argv[0]=xstrdup(WIN32_module_name);
    /* Scan command line until there is nothing left. */

    while (*cmd) {
        /* Ignore spaces */

        if (xisspace(*cmd)) {
            cmd++;
            continue;
        }

        /* Found the beginning of an argument. */
        word = cmd;

        while (*cmd) {
            cmd++;		/* Skip over this character */

            if (xisspace(*cmd))	/* End of argument if space */
                break;
        }

        if (*cmd)
            *cmd++ = '\0';		/* Terminate `word' */

        /* See if we need to allocate more space for argv */
        if (WIN32_argc >= argvlen) {
            argvlen = WIN32_argc + 1;
            WIN32_argv = (char **) xrealloc (WIN32_argv, (1 + argvlen) * sizeof (char *));
        }

        /* Add word to argv file. */
        WIN32_argv[WIN32_argc++] = word;
    }

    WIN32_argv[WIN32_argc] = NULL;
}