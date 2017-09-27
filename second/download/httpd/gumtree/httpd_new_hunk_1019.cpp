    if (parse_url(apr_pstrdup(cntxt, opt->argv[opt->ind++]))) {
	fprintf(stderr, "%s: invalid URL\n", argv[0]);
	usage(argv[0]);
    }

    if ((concurrency < 0) || (concurrency > MAX_CONCURRENCY)) {
        fprintf(stderr, "%s: Invalid Concurrency [Range 0..%d]\n",
                argv[0], MAX_CONCURRENCY);
        usage(argv[0]);
    }

    if (concurrency > requests) {
        fprintf(stderr, "%s: Cannot use concurrency level greater than "
                "total number of requests\n", argv[0]);
        usage(argv[0]);
    }

    if ((heartbeatres) && (requests > 150)) {
	heartbeatres = requests / 10;	/* Print line every 10% of requests */
	if (heartbeatres < 100)
	    heartbeatres = 100;	/* but never more often than once every 100
				 * connections. */
    }
