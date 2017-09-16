	case 'l':

	    ap_show_modules();

	    exit(0);

	case 'X':

	    ++one_process;	/* Weird debugging mode. */

	    break;

	case '?':

	    usage(argv[0]);

	}

    }



    if (!child && run_as_service) {

	service_cd();

    }



    server_conf = ap_read_config(pconf, ptrans, ap_server_confname);

    if (!child) {

	ap_log_pid(pconf, ap_pid_fname);

    }

    ap_set_version();

    ap_init_modules(pconf, server_conf);

    ap_suexec_enabled = init_suexec();

