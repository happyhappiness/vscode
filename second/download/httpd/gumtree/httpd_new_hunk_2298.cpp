	     */
	    break;
#endif
	case 'S':
	    ap_dump_settings = 1;
	    break;
	case 't':
	    configtestonly = 1;
	    break;
	case '?':
	    usage(argv[0]);
	}
    }

    ap_suexec_enabled = init_suexec();
    server_conf = ap_read_config(pconf, ptrans, ap_server_confname);

    if (configtestonly) {
        fprintf(stderr, "Syntax OK\n");
        exit(0);
    }

    child_timeouts = !ap_standalone || one_process;

    if (ap_standalone) {
	ap_open_logs(server_conf, pconf);
	ap_set_version();
	ap_init_modules(pconf, server_conf);
