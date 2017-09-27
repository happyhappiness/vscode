	     * needs to be extended to handle whatever servers folks want to
	     * test against. -djg
	     */

	    /* check response code */
	    part = strstr(c->cbuff, "HTTP");	/* really HTTP/1.x_ */
            if (part && strlen(part) > strlen("HTTP/1.x_")) {
                strncpy(respcode, (part + strlen("HTTP/1.x_")), 3);
                respcode[3] = '\0';
            }
            else {
                strcpy(respcode, "500");
            }

	    if (respcode[0] != '2') {
		err_response++;
		if (verbosity >= 2)
		    printf("WARNING: Response code not 2xx (%s)\n", respcode);
	    }
	    else if (verbosity >= 3) {
