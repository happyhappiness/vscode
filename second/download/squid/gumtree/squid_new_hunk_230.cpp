
            break;

        case 'v':
            /** \par v
             * Display squid version and build information. Then exit. */
            printf("Squid Cache: Version %s\n" ,version_string);
            if (strlen(SQUID_BUILD_INFO))
                printf("%s\n",SQUID_BUILD_INFO);
            printf( "configure options: %s\n", SQUID_CONFIGURE_OPTIONS);

#if USE_WIN32_SERVICE

            printf("Compiled as Windows System Service.\n");

#endif
