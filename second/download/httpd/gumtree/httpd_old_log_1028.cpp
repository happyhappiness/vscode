fprintf(stderr, "Usage: %s [options] [http"
#if USE_SSL
	    "[s]"
#endif
	    "://]hostname[:port]/path\n", progname);