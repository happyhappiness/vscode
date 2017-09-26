	apr_size_t space = CBUFFSIZE - c->cbx - 1; /* -1 allows for \0 term */
	int tocopy = (space < r) ? space : r;
#ifdef NOT_ASCII
	apr_size_t inbytes_left = space, outbytes_left = space;

	status = apr_xlate_conv_buffer(from_ascii, buffer, &inbytes_left,
				       c->cbuff + c->cbx, &outbytes_left);
	if (status || inbytes_left || outbytes_left) {
	    fprintf(stderr, "only simple translation is supported (%d/%u/%u)\n",
		    status, inbytes_left, outbytes_left);
	    exit(1);
	}
#else
	memcpy(c->cbuff + c->cbx, buffer, space);
#endif				/* NOT_ASCII */
	c->cbx += tocopy;
	space -= tocopy;
	c->cbuff[c->cbx] = 0;	/* terminate for benefit of strstr */
        if (verbosity >= 2) {
	    printf("LOG: header received:\n%s\n", c->cbuff);
	}
