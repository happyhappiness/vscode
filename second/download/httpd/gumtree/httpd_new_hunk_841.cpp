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

nly in apache_1.3.0/src/support: Makefile

