    }

    else {

        ap_rputs(anchor, r);

    }

}



/*

 * Fit a string into a specified buffer width, marking any

 * truncation.  The size argument is the actual buffer size, including

 * the \0 termination byte.  The buffer will be prefilled with blanks.

 * If the pad argument is false, any extra spaces at the end of the

 * buffer are omitted.  (Used when constructing anchors.)

 */

static ap_inline char *widthify(const char *s, char *buff, int size, int pad)

{

    int s_len;



    memset(buff, ' ', size);

    buff[size - 1] = '\0';

    s_len = strlen(s);

    if (s_len > (size - 1)) {

	ap_cpystrn(buff, s, size);

	if (size > 1) {

	    buff[size - 2] = '>';

	}

	if (size > 2) {

	    buff[size - 3] = '.';

	}

	if (size > 3) {

	    buff[size - 4] = '.';

	}

    }

    else {

	ap_cpystrn(buff, s, s_len + 1);

	if (pad) {

	    buff[s_len] = ' ';

	}

    }

    return buff;

}



static void output_directories(struct ent **ar, int n,

			       autoindex_config_rec *d, request_rec *r,

			       int autoindex_opts, char keyid, char direction)

{

    int x;

    char *name = r->uri;

    char *tp;

    int static_columns = (autoindex_opts & SUPPRESS_COLSORT);

    pool *scratch = ap_make_sub_pool(r->pool);

    int name_width;

    char *name_scratch;



    if (name[0] == '\0') {

	name = "/";

    }



    name_width = d->name_width;

    if (d->name_adjust) {

	for (x = 0; x < n; x++) {

	    int t = strlen(ar[x]->name);

	    if (t > name_width) {

		name_width = t;

	    }

	}

    }

    ++name_width;

    name_scratch = ap_palloc(r->pool, name_width + 1);

    memset(name_scratch, ' ', name_width);

    name_scratch[name_width] = '\0';



    if (autoindex_opts & FANCY_INDEXING) {

	ap_rputs("<PRE>", r);

	if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {

	    ap_rvputs(r, "<IMG SRC=\"", ap_escape_html(scratch, tp),

		   "\" ALT=\"     \"", NULL);

