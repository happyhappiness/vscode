	  break;

	case 'B':
	  block_size = atoi(optarg);
	  break;

        case 'z':
	  do_compression = 1;
	  break;

	default:
	  /* fprintf(FERROR,"bad option -%c\n",opt); */
	  exit_cleanup(1);
	}
    }

    while (optind--) {
      argc--;
