
            break;

        case 'v':
            /** \par v
             * Display squid version and build information. Then exit. */
            printf("Squid Cache: Version %s\nconfigure options: %s\n", version_string, SQUID_CONFIGURE_OPTIONS);

#if USE_WIN32_SERVICE

            printf("Compiled as Windows System Service.\n");

#endif
