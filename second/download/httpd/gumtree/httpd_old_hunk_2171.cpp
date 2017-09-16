		ap_rputs(">", r);

	    }

	    if (autoindex_opts & ICONS_ARE_LINKS) {

		ap_rputs("</A>", r);

	    }



	    ap_rvputs(r, " ", anchor, t2, NULL);

	    if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {

		if (ar[x]->lm != -1) {

		    char time_str[MAX_STRING_LEN];

		    struct tm *ts = localtime(&ar[x]->lm);

		    strftime(time_str, MAX_STRING_LEN, "%d-%b-%Y %H:%M  ", ts);

		    ap_rputs(time_str, r);

