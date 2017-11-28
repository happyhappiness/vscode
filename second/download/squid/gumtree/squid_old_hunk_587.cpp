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
