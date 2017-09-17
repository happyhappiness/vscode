    }
    else {
	ap_rputs("<UL>", r);
    }

    for (x = 0; x < n; x++) {
	char *anchor, *t, *t2;
	char *pad;
	int nwidth;

	ap_clear_pool(scratch);

	if (is_parent(ar[x]->name)) {
	    t = ap_make_full_path(scratch, name, "../");
	    ap_getparents(t);
	    if (t[0] == '\0') {
		t = "/";
	    }
	       /* 1234567890123456 */
	    t2 = "Parent Directory";
	    pad = name_scratch + 16;
	    anchor = ap_escape_html(scratch, ap_os_escape_path(scratch, t, 0));
	}
	else {
	    t = ar[x]->name;
	    pad = name_scratch + strlen(t);
	    t2 = ap_escape_html(scratch, t);
	    anchor = ap_escape_html(scratch, ap_os_escape_path(scratch, t, 0));
	}

	if (autoindex_opts & FANCY_INDEXING) {
	    if (autoindex_opts & ICONS_ARE_LINKS) {
		ap_rvputs(r, "<A HREF=\"", anchor, "\">", NULL);
	    }
	    if ((ar[x]->icon) || d->default_icon) {
		ap_rvputs(r, "<IMG SRC=\"",
			  ap_escape_html(scratch,
					 ar[x]->icon ? ar[x]->icon
					             : d->default_icon),
