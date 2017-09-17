	    if (!(autoindex_opts & SUPPRESS_SIZE)) {
		ap_send_size(ar[x]->size, r);
		ap_rputs("  ", r);
	    }
	    if (!(autoindex_opts & SUPPRESS_DESC)) {
		if (ar[x]->desc) {
		    ap_rputs(terminate_description(d, ar[x]->desc, autoindex_opts), r);
		}
	    }
	}
	else
	    ap_rvputs(r, "<LI> ", anchor, " ", t2, NULL);
	ap_rputc('\n', r);
    }
    if (autoindex_opts & FANCY_INDEXING) {
	ap_rputs("</PRE>", r);
    }
    else {
	ap_rputs("</UL>", r);
    }
}


static int dsortf(struct ent **e1, struct ent **e2)
{
    char *s1;
    char *s2;
    char *s3;
    int result;

    /*
     * Choose the right values for the sort keys.
     */
    switch ((*e1)->key) {
    case K_LAST_MOD:
	s1 = (*e1)->lm_cmp;
	s2 = (*e2)->lm_cmp;
	break;
    case K_SIZE:
	s1 = (*e1)->size_cmp;
	s2 = (*e2)->size_cmp;
	break;
    case K_DESC:
	s1 = (*e1)->desc;
	s2 = (*e2)->desc;
	break;
    case K_NAME:
    default:
	s1 = (*e1)->name;
	s2 = (*e2)->name;
	break;
    }
    /*
     * If we're supposed to sort in DEscending order, reverse the arguments.
     */
    if (!(*e1)->ascending) {
	s3 = s1;
	s1 = s2;
	s2 = s3;
    }

    /*
     * Take some care, here, in case one string or the other (or both) is
     * NULL.
     */

    /*
     * Two valid strings, compare normally.
     */
    if ((s1 != NULL) && (s2 != NULL)) {
	result = strcmp(s1, s2);
    }
    /*
     * Two NULL strings - primary keys are equal (fake it).
     */
    else if ((s1 == NULL) && (s2 == NULL)) {
	result = 0;
    }
    /*
     * s1 is NULL, but s2 is a string - so s2 wins.
     */
    else if (s1 == NULL) {
	result = -1;
    }
    /*
     * Last case: s1 is a string and s2 is NULL, so s1 wins.
     */
    else {
	result = 1;
    }
    /*
     * If the keys were equal, the file name is *always* the secondary key -
     * in ascending order.
     */
    if (!result) {
	result = strcmp((*e1)->name, (*e2)->name);
    }
    return result;
}


static int index_directory(request_rec *r, autoindex_config_rec * autoindex_conf)
{
    char *title_name = ap_escape_html(r->pool, r->uri);
