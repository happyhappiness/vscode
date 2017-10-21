				    "Invalid argument passed to --chmod (%s)\n",
				    arg);
				return 0;
			}
			break;

		case OPT_HELP:
			usage(FINFO);
			exit_cleanup(0);

		case 'A':
#ifdef SUPPORT_ACLS
