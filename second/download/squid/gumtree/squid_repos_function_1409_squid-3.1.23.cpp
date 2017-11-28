static void
mainParseOptions(int argc, char *argv[])
{
    extern char *optarg;
    int c;

#if USE_WIN32_SERVICE
    while ((c = getopt(argc, argv, "CDFNO:RSVYXa:d:f:hik:m::n:rsl:u:vz?")) != -1)
#else
    while ((c = getopt(argc, argv, "CDFNRSYXa:d:f:hk:m::sl:u:vz?")) != -1)
#endif
    {

        switch (c) {

        case 'C':
            /** \par C
             * Unset/disabel global option for catchign signals. opt_catch_signals */
            opt_catch_signals = 0;
            break;

        case 'D':
            /** \par D
             * OBSOLETE: WAS: override to prevent optional startup DNS tests. */
            debugs(1,DBG_CRITICAL, "WARNING: -D command-line option is obsolete.");
            break;

        case 'F':
            /** \par F
             * Set global option for foreground rebuild. opt_foreground_rebuild */
            opt_foreground_rebuild = 1;
            break;

        case 'N':
            /** \par N
             * Set global option for 'no_daemon' mode. opt_no_daemon */
            opt_no_daemon = 1;
            break;

#if USE_WIN32_SERVICE

        case 'O':
            /** \par O
             * Set global option. opt_command_lin and WIN32_Command_Line */
            opt_command_line = 1;
            WIN32_Command_Line = xstrdup(optarg);
            break;
#endif

        case 'R':
            /** \par R
             * Unset/disable global option opt_reuseaddr */
            opt_reuseaddr = 0;
            break;

        case 'S':
            /** \par S
             * Set global option opt_store_doublecheck */
            opt_store_doublecheck = 1;
            break;

        case 'X':
            /** \par X
             * Force full debugging */
            Debug::parseOptions("rotate=0 ALL,9");
            Debug::override_X = 1;
            sigusr2_handle(SIGUSR2);
            break;

        case 'Y':
            /** \par Y
             * Set global option opt_reload_hit_only */
            opt_reload_hit_only = 1;
            break;

#if USE_WIN32_SERVICE

        case 'i':
            /** \par i
             * Set global option opt_install_service (to TRUE) */
            opt_install_service = TRUE;
            break;
#endif

        case 'a':
            /** \par a
             * Add optional HTTP port as given following the option */
            add_http_port(optarg);
            break;

        case 'd':
            /** \par d
             * Set global option Debug::log_stderr to the number given follwoign the option */
            Debug::log_stderr = atoi(optarg);
            break;

        case 'f':
            /** \par f
             * Load the file given instead of the default squid.conf. */
            xfree(ConfigFile);
            ConfigFile = xstrdup(optarg);
            break;

        case 'k':
            /** \par k
             * Run the administrative action given following the option */

            /** \li When its an unknown option display the usage help. */
            if ((int) strlen(optarg) < 1)
                usage();

            if (!strncmp(optarg, "reconfigure", strlen(optarg)))
                /** \li On reconfigure send SIGHUP. */
                opt_send_signal = SIGHUP;
            else if (!strncmp(optarg, "rotate", strlen(optarg)))
                /** \li On rotate send SIGQUIT or SIGUSR1. */
#ifdef _SQUID_LINUX_THREADS_

                opt_send_signal = SIGQUIT;

#else

                opt_send_signal = SIGUSR1;

#endif

            else if (!strncmp(optarg, "debug", strlen(optarg)))
                /** \li On debug send SIGTRAP or SIGUSR2. */
#ifdef _SQUID_LINUX_THREADS_

                opt_send_signal = SIGTRAP;

#else

                opt_send_signal = SIGUSR2;

#endif

            else if (!strncmp(optarg, "shutdown", strlen(optarg)))
                /** \li On shutdown send SIGTERM. */
                opt_send_signal = SIGTERM;
            else if (!strncmp(optarg, "interrupt", strlen(optarg)))
                /** \li On interrupt send SIGINT. */
                opt_send_signal = SIGINT;
            else if (!strncmp(optarg, "kill", strlen(optarg)))
                /** \li On kill send SIGKILL. */
                opt_send_signal = SIGKILL;

#ifdef SIGTTIN

            else if (!strncmp(optarg, "restart", strlen(optarg)))
                /** \li On restart send SIGTTIN. (exit and restart by parent) */
                opt_send_signal = SIGTTIN;

#endif

            else if (!strncmp(optarg, "check", strlen(optarg)))
                /** \li On check send 0 / SIGNULL. */
                opt_send_signal = 0;	/* SIGNULL */
            else if (!strncmp(optarg, "parse", strlen(optarg)))
                /** \li On parse set global flag to re-parse the config file only. */
                opt_parse_cfg_only = 1;
            else
                usage();

            break;

        case 'm':
            /** \par m
             * Set global malloc_debug_level to the value given following the option.
             * if none is given it toggles the xmalloc_trace option on/off */
            if (optarg) {
#if MALLOC_DBG
                malloc_debug_level = atoi(optarg);
#else
                fatal("Need to add -DMALLOC_DBG when compiling to use -mX option");
#endif

            } else {
#if XMALLOC_TRACE
                xmalloc_trace = !xmalloc_trace;
#else
                fatal("Need to configure --enable-xmalloc-debug-trace to use -m option");
#endif
            }
            break;

#if USE_WIN32_SERVICE

        case 'n':
            /** \par n
             * Set global option opt_signal_service (to TRUE).
             * Stores the additional parameter given in global WIN32_Service_name */
            xfree(WIN32_Service_name);

            WIN32_Service_name = xstrdup(optarg);

            opt_signal_service = TRUE;

            break;

        case 'r':
            /** \par r
             * Set global option opt_remove_service (to TRUE) */
            opt_remove_service = TRUE;

            break;

#endif

        case 'l':
            /** \par l
             * Stores the syslog facility name in global opt_syslog_facility
             * then performs actions for -s option. */
            opt_syslog_facility = xstrdup(optarg);

        case 's':
            /** \par s
             * Initialize the syslog for output */
#if HAVE_SYSLOG

            _db_set_syslog(opt_syslog_facility);

            break;

#else

            fatal("Logging to syslog not available on this platform");

            /* NOTREACHED */
#endif

        case 'u':
            /** \par u
             * Store the ICP port number given in global option icpPortNumOverride
             * ensuring its a positive number. */
            icpPortNumOverride = atoi(optarg);

            if (icpPortNumOverride < 0)
                icpPortNumOverride = 0;

            break;

        case 'v':
            /** \par v
             * Display squid version and build information. Then exit. */
            printf("Squid Cache: Version %s\nconfigure options: %s\n", version_string, SQUID_CONFIGURE_OPTIONS);

#if USE_WIN32_SERVICE

            printf("Compiled as Windows System Service.\n");

#endif

            exit(0);

            /* NOTREACHED */

        case 'z':
            /** \par z
             * Set global option Debug::log_stderr and opt_create_swap_dirs */
            Debug::log_stderr = 1;
            opt_create_swap_dirs = 1;
            break;

        case 'h':

        case '?':

        default:
            /** \par h,?, or unknown
             * \copydoc usage() */
            usage();

            break;
        }

    }
}