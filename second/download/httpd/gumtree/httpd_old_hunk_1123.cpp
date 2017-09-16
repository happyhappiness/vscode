	    int cond_status = OK;



	    ap_kill_timeout(r);

	    if ((cgi_status == HTTP_OK) && (r->method_number == M_GET)) {

		cond_status = ap_meets_conditions(r);

	    }

	    return cond_status;

	}



	/* if we see a bogus header don't ignore it. Shout and scream */



	if (!(l = strchr(w, ':'))) {

	    char malformed[(sizeof MALFORMED_MESSAGE) + 1

			   + MALFORMED_HEADER_LENGTH_TO_SHOW];



	    strcpy(malformed, MALFORMED_MESSAGE);

	    strncat(malformed, w, MALFORMED_HEADER_LENGTH_TO_SHOW);

