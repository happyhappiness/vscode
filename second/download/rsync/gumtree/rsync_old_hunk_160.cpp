
	case 'B':
	  block_size = atoi(optarg);
	  break;

	default:
	  fprintf(stderr,"bad option -%c\n",opt);
	  exit_cleanup(1);
	}
    }

    while (optind--) {
      argc--;
