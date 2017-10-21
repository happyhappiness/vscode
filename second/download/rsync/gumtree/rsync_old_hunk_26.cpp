	  break;

	default:
	  fprintf(stderr,"bad option -%c\n",opt);
	  exit(1);
	}

    while (optind--) {
      argc--;
      argv++;
    }

