
    ap_kill_timeout(r);
    return total_bytes_rcv;
}

/*
 * Read a header from the array, returning the first entry
 */
struct hdr_entry *
          ap_proxy_get_header(array_header *hdrs_arr, const char *name)
{
    struct hdr_entry *hdrs;
    int i;

    hdrs = (struct hdr_entry *) hdrs_arr->elts;
    for (i = 0; i < hdrs_arr->nelts; i++)
	if (hdrs[i].field != NULL && strcasecmp(name, hdrs[i].field) == 0)
	    return &hdrs[i];

    return NULL;
}

/*
 * Add to the header reply, either concatenating, or replacing existin
 * headers. It stores the pointers provided, so make sure the data
 * is not subsequently overwritten
 */
struct hdr_entry *
          ap_proxy_add_header(array_header *hdrs_arr, const char *field, const char *value,
			   int rep)
{
    int i;
    struct hdr_entry *hdrs;

    hdrs = (struct hdr_entry *) hdrs_arr->elts;
    if (rep)
	for (i = 0; i < hdrs_arr->nelts; i++)
	    if (hdrs[i].field != NULL && strcasecmp(field, hdrs[i].field) == 0) {
		hdrs[i].value = value;
		return hdrs;
	    }

    hdrs = ap_push_array(hdrs_arr);
    hdrs->field = field;
    hdrs->value = value;

    return hdrs;
}

void ap_proxy_del_header(array_header *hdrs_arr, const char *field)
{
    int i;
    struct hdr_entry *hdrs;

    hdrs = (struct hdr_entry *) hdrs_arr->elts;

    for (i = 0; i < hdrs_arr->nelts; i++)
	if (hdrs[i].field != NULL && strcasecmp(field, hdrs[i].field) == 0)
	    hdrs[i].value = NULL;
}

/*
 * Sends response line and headers.  Uses the client fd and the 
 * headers_out array from the passed request_rec to talk to the client
 * and to properly set the headers it sends for things such as logging.
 * 
 * A timeout should be set before calling this routine.
 */
void ap_proxy_send_headers(request_rec *r, const char *respline, array_header *hdrs_arr)
{
    struct hdr_entry *hdrs;
    int i;
    BUFF *fp = r->connection->client;

    hdrs = (struct hdr_entry *) hdrs_arr->elts;

    ap_bputs(respline, fp);
    ap_bputs(CRLF, fp);
    for (i = 0; i < hdrs_arr->nelts; i++) {
	if (hdrs[i].field == NULL)
	    continue;
	ap_bvputs(fp, hdrs[i].field, ": ", hdrs[i].value, CRLF, NULL);
	ap_table_set(r->headers_out, hdrs[i].field, hdrs[i].value);
    }

    ap_bputs(CRLF, fp);
}


