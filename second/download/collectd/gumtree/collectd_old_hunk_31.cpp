				break;

			case 'l':
				operating_mode = MODE_LOCAL;
				break;
#endif /* HAVE_LIBRRD */
			case 'd':
				basedir = optarg;
				break;
			case 'f':
				daemonize = 0;
				break;
#if COLLECT_PING
			case 'p':
				if (num_pinghosts < MAX_PINGHOSTS)
					pinghosts[num_pinghosts++] = optarg;
				else
					fprintf (stderr, "Maximum of %i ping hosts reached.\n", MAX_PINGHOSTS);
				break;
#endif /* COLLECT_PING */
			case 'P':
				plugindir = optarg;
				break;

			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}
