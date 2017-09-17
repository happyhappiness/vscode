    if ((r->method_number == M_POST || r->method_number == M_PUT)
	&& *dbuf) {
	fprintf(f, "\n%s\n", dbuf);
    }

    fputs("%response\n", f);
    hdrs_arr = ap_table_elts(r->err_headers_out);
    hdrs = (table_entry *) hdrs_arr->elts;

    for (i = 0; i < hdrs_arr->nelts; ++i) {
	if (!hdrs[i].key)
	    continue;
	fprintf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val);
