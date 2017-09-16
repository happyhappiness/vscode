#ifdef SHARED_CORE

    fprintf(stderr, "Usage: %s [-L directory] [-d directory] [-f file]\n", bin);

#else

    fprintf(stderr, "Usage: %s [-d directory] [-f file]\n", bin);

#endif

    fprintf(stderr, "       %s [-C \"directive\"] [-c \"directive\"]\n", pad);

    fprintf(stderr, "       %s [-v] [-V] [-h] [-l] [-S]\n", pad);

    fprintf(stderr, "Options:\n");

#ifdef SHARED_CORE

    fprintf(stderr, "  -L directory     : specify an alternate location for shared object files\n");

#endif

    fprintf(stderr, "  -d directory     : specify an alternate initial ServerRoot\n");

    fprintf(stderr, "  -f file          : specify an alternate ServerConfigFile\n");

    fprintf(stderr, "  -C \"directive\"   : process directive before reading config files\n");

    fprintf(stderr, "  -c \"directive\"   : process directive after  reading config files\n");

    fprintf(stderr, "  -v               : show version number\n");

    fprintf(stderr, "  -V               : show compile settings\n");

    fprintf(stderr, "  -h               : list available configuration directives\n");

    fprintf(stderr, "  -l               : list compiled-in modules\n");

    fprintf(stderr, "  -S               : show parsed settings (currently only vhost settings)\n");

    exit(1);

}



/*****************************************************************

 *

 * Timeout handling.  DISTINCTLY not thread-safe, but all this stuff

