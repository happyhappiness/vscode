    }

    else {

        ap_rputs(anchor, r);

    }

}



static void output_directories(struct ent **ar, int n,

			       autoindex_config_rec * d, request_rec *r,

			     int autoindex_opts, char keyid, char direction)

{

    int x, len;

    char *name = r->uri;

    char *tp;

    int static_columns = (autoindex_opts & SUPPRESS_COLSORT);

    pool *scratch = ap_make_sub_pool(r->pool);



    if (name[0] == '\0')

	name = "/";



    if (autoindex_opts & FANCY_INDEXING) {

	ap_rputs("<PRE>", r);

	if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {

	    ap_rvputs(r, "<IMG SRC=\"", ap_escape_html(scratch, tp),

		   "\" ALT=\"     \"", NULL);

