                fatal("Need to add -DMALLOC_DBG when compiling to use -mX option");
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
