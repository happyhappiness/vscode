	totalbread += r;
    }

    if (c->keepalive && (c->bread >= c->length)) {
	/* finished a keep-alive connection */
	good++;
	doneka++;
	/* save out time */
	if (good == 1) {
	    /* first time here */
	    doclen = c->bread;
	}
	else if (c->bread != doclen) {
	    bad++;
	    err_length++;
	}
	if (done < requests) {
	    struct data s;
	    if (done && heartbeatres && !(done % heartbeatres)) {
		fprintf(stderr, "Completed %ld requests\n", done);
		fflush(stderr);
	    }
	    c->done = apr_time_now();
	    s.read = c->read;
