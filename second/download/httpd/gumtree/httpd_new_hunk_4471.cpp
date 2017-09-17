		exit(1);
	    }
	    i++;
	    statfile = argv[i];
	}
	else {
	    fprintf(stderr, "Usage: logresolve [-s statfile] [-c] < input > output\n");
	    exit(0);
	}
    }


    for (i = 0; i < BUCKETS; i++)
++ apache_1.3.1/src/support/rotatelogs.c	1998-07-13 19:32:58.000000000 +0800
