#else
	memcpy(c->cbuff + c->cbx, buffer, space);
#endif				/* NOT_ASCII */
	c->cbx += tocopy;
	space -= tocopy;
	c->cbuff[c->cbx] = 0;	/* terminate for benefit of strstr */
	if (verbosity >= 4) {
	    printf("LOG: header received:\n%s\n", c->cbuff);
	}
	s = strstr(c->cbuff, "\r\n\r\n");
	/*
	 * this next line is so that we talk to NCSA 1.5 which blatantly
	 * breaks the http specifaction
