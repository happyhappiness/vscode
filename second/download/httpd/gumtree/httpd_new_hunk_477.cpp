		char buff[24] = "                       ";

		t2 = ap_escape_html(scratch, t);

		buff[23 - len] = '\0';

		t2 = ap_pstrcat(scratch, t2, "</A>", buff, NULL);

	    }

	    anchor = ap_pstrcat(scratch, "<A HREF=\"",

				ap_escape_html(scratch,

					       ap_os_escape_path(scratch, t,

								 0)),

				"\">", NULL);

	}



	if (autoindex_opts & FANCY_INDEXING) {

	    if (autoindex_opts & ICONS_ARE_LINKS) {

		ap_rputs(anchor, r);

	    }

	    if ((ar[x]->icon) || d->default_icon) {

		ap_rvputs(r, "<IMG SRC=\"",

			  ap_escape_html(scratch,

					 ar[x]->icon ? ar[x]->icon

					             : d->default_icon),

			  "\" ALT=\"[", (ar[x]->alt ? ar[x]->alt : "   "),

			  "]\"", NULL);

		if (d->icon_width && d->icon_height) {

		    ap_rprintf(r, " HEIGHT=\"%d\" WIDTH=\"%d\"",

			       d->icon_height, d->icon_width);

		}

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

