	secring = 1;
	break;
      }
    
      default:
      {
	fprintf (stderr, "usage: %s [-k <key ring> | [-2 | -5] [ -s] [-S] [-f]] [hints]\n",
		 argv[0]);
	exit (1);
      }
    }
  }

