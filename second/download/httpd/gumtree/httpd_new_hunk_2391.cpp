		ap_rputs(">", r);

	    }

	    if (autoindex_opts & ICONS_ARE_LINKS) {

		ap_rputs("</A>", r);

	    }



	    ap_rvputs(r, " <A HREF=\"", anchor, "\">",

		      widthify(t2, name_scratch, name_width, K_NOPAD),

		      "</A>", NULL);

	    /*

	     * We know that widthify() prefilled the buffer with spaces

	     * before doing its thing, so use them.

	     */

	    nwidth = strlen(t2);

	    if (nwidth < (name_width - 1)) {

		name_scratch[nwidth] = ' ';

		ap_rputs(&name_scratch[nwidth], r);

	    }

	    /*

	     * The blank before the storm.. er, before the next field.

	     */

	    ap_rputs(" ", r);

	    if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {

		if (ar[x]->lm != -1) {

		    char time_str[MAX_STRING_LEN];

		    struct tm *ts = localtime(&ar[x]->lm);

		    strftime(time_str, MAX_STRING_LEN, "%d-%b-%Y %H:%M  ", ts);

		    ap_rputs(time_str, r);

