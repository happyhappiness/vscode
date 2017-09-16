		exit(1);

	    }

	    i++;

	    statfile = argv[i];

	}

	else {

	    fprintf(stderr, "Usage: logresolve [-s statfile] [-c] < input > output");

	    exit(0);

	}

    }





    for (i = 0; i < BUCKETS; i++)

nly in apache_1.3.0/src/support: Makefile

-- apache_1.3.0/src/support/rotatelogs.c	1998-04-22 04:14:06.000000000 +0800

