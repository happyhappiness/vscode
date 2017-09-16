    ap_bvputs(f, "Host: ", desthost, NULL);

    if (destportstr != NULL && destport != DEFAULT_HTTP_PORT)

	ap_bvputs(f, ":", destportstr, CRLF, NULL);

    else

	ap_bputs(CRLF, f);



    reqhdrs_arr = ap_table_elts(r->headers_in);

    reqhdrs = (table_entry *) reqhdrs_arr->elts;

    for (i = 0; i < reqhdrs_arr->nelts; i++) {

	if (reqhdrs[i].key == NULL || reqhdrs[i].val == NULL

	/* Clear out headers not to send */

	    || !strcasecmp(reqhdrs[i].key, "Host")	/* Already sent */

	    ||!strcasecmp(reqhdrs[i].key, "Proxy-Authorization"))

