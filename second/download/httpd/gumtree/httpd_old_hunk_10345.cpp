    }
    else {
	ap_rputs("<UL>", r);
    }

    for (x = 0; x < n; x++) {
	char *anchor = NULL, *t = NULL, *t2 = NULL;

	ap_clear_pool(scratch);

	if (is_parent(ar[x]->name)) {
	    t = ap_make_full_path(scratch, name, "../");
	    ap_getparents(t);
	    if (t[0] == '\0') {
		t = "/";
	    }
	    anchor = ap_pstrcat(scratch, "<A HREF=\"",
				ap_escape_html(scratch,
					       ap_os_escape_path(scratch, t,
								 0)),
				"\">", NULL);
	    t2 = "Parent Directory</A>       ";
	}
	else {
	    t = ar[x]->name;
	    len = strlen(t);
	    if (len > 23) {
		t2 = ap_pstrdup(scratch, t);
		t2[21] = '.';
		t2[22] = '.';
		t2[23] = '\0';
		t2 = ap_escape_html(scratch, t2);
		t2 = ap_pstrcat(scratch, t2, "</A>", NULL);
	    }
	    else {
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
