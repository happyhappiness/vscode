    q = ap_palloc(p, 30);

    ap_snprintf(q, 30, "%s, %.2d %s %d %.2d:%.2d:%.2d GMT", ap_day_snames[wk], mday,

		ap_month_snames[mon], year, hour, min, sec);

    return q;

}



/*

 * Reads headers from a buffer and returns an array of headers.

 * Returns NULL on file error

 */

array_header *

             ap_proxy_read_headers(pool *p, char *buffer, int size, BUFF *f)

{

    int gotcr, len, i, j;

    array_header *resp_hdrs;

    struct hdr_entry *hdr;

    char *strp;

    const char *strcp;



    resp_hdrs = ap_make_array(p, 10, sizeof(struct hdr_entry));

    hdr = NULL;



    gotcr = 1;

    for (;;) {

	len = ap_bgets(buffer, size, f);

	if (len == -1)

	    return NULL;

	if (len == 0)

	    break;

	if (buffer[len - 1] == '\n') {

	    buffer[--len] = '\0';

	    i = 1;

	}

	else

	    i = 0;



	if (!gotcr || buffer[0] == ' ' || buffer[0] == '\t') {

	    /* a continuation header */

	    if (hdr == NULL) {

		/* error!! */

		if (!i) {

		    i = ap_bskiplf(f);

		    if (i == -1)

			return NULL;

		}

		gotcr = 1;

		continue;

	    }

	    hdr->value = ap_pstrcat(p, hdr->value, buffer, NULL);

	}

	else if (gotcr && len == 0)

	    break;

	else {

	    strp = strchr(buffer, ':');

	    if (strp == NULL) {

		/* error!! */

		if (!gotcr) {

		    i = ap_bskiplf(f);

		    if (i == -1)

			return NULL;

		}

		gotcr = 1;

		hdr = NULL;

		continue;

	    }

	    hdr = ap_push_array(resp_hdrs);

	    *(strp++) = '\0';

	    hdr->field = ap_pstrdup(p, buffer);

	    while (*strp == ' ' || *strp == '\t')

		strp++;

	    hdr->value = ap_pstrdup(p, strp);

	    gotcr = i;

	}

    }



    hdr = (struct hdr_entry *) resp_hdrs->elts;

    for (i = 0; i < resp_hdrs->nelts; i++) {

	strcp = hdr[i].value;

	j = strlen(strcp);

	while (j > 0 && (strcp[j - 1] == ' ' || strcp[j - 1] == '\t'))

	    j--;

	/* Note that this is OK, coz we created the header above */

	((char *)strcp)[j] = '\0';

    }



    return resp_hdrs;

}



long int ap_proxy_send_fb(BUFF *f, request_rec *r, BUFF *f2, struct cache_req *c)

{

    int  ok = 1;

    char buf[IOBUFSIZE];

    long total_bytes_rcv;

    register int n, o, w;

    conn_rec *con = r->connection;

