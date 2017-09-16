 */



/*

 * Look for the specified file, and pump it into the response stream if we

 * find it.

 */

static int insert_readme(char *name, char *readme_fname, char *title, int hrule,

			 int whichend, request_rec *r)

{

    char *fn;

    FILE *f;

    struct stat finfo;

    int plaintext = 0;

    request_rec *rr;

    autoindex_config_rec *cfg =

    (autoindex_config_rec *) ap_get_module_config

    (

	r->per_dir_config,

	&autoindex_module

    );

    int autoindex_opts = find_opts(cfg, r);



    /* XXX: this is a load of crap, it needs to do a full sub_req_lookup_uri */

    fn = ap_make_full_path(r->pool, name, readme_fname);

    fn = ap_pstrcat(r->pool, fn, ".html", NULL);

    if (stat(fn, &finfo) == -1) {

	/* A brief fake multiviews search for README.html */

	fn[strlen(fn) - 5] = '\0';

	if (stat(fn, &finfo) == -1)

	    return 0;

	plaintext = 1;

	if (hrule)

	    ap_rputs("<HR>\n", r);

    }

    else if (hrule)

	ap_rputs("<HR>\n", r);

    /* XXX: when the above is rewritten properly, this necessary security

     * check will be redundant. -djg */

    rr = ap_sub_req_lookup_file(fn, r);

    if (rr->status != HTTP_OK) {

	ap_destroy_sub_req(rr);

	return 0;

    }

    ap_destroy_sub_req(rr);

    if (!(f = ap_pfopen(r->pool, fn, "r")))

	     return 0;

    if (

	   (whichend == FRONT_MATTER) &&

	   (!(autoindex_opts & SUPPRESS_PREAMBLE))

	) {

	emit_preamble(r, title);

    }

    if (!plaintext) {

	ap_send_fd(f, r);

    }

    else {

	char buf[IOBUFSIZE + 1];

	int i, n, c, ch;

	ap_rputs("<PRE>\n", r);

	while (!feof(f)) {

	    do

		n = fread(buf, sizeof(char), IOBUFSIZE, f);

	    while (n == -1 && ferror(f) && errno == EINTR);

	    if (n == -1 || n == 0)

		break;

	    buf[n] = '\0';

	    c = 0;

	    while (c < n) {

		for (i = c; i < n; i++)

		    if (buf[i] == '<' || buf[i] == '>' || buf[i] == '&')

			break;

		ch = buf[i];

		buf[i] = '\0';

		ap_rputs(&buf[c], r);

		if (ch == '<')

		    ap_rputs("&lt;", r);

		else if (ch == '>')

		    ap_rputs("&gt;", r);

		else if (ch == '&')

		    ap_rputs("&amp;", r);

		c = i + 1;

	    }

	}

    }

    ap_pfclose(r->pool, f);

    if (plaintext)

	ap_rputs("</PRE>\n", r);

    return 1;

}





static char *find_title(request_rec *r)

{

