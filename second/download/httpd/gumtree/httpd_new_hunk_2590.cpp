

    ap_kill_timeout(r);

    return total_bytes_rcv;

}



/*

 * Sends response line and headers.  Uses the client fd and the 

 * headers_out array from the passed request_rec to talk to the client

 * and to properly set the headers it sends for things such as logging.

 * 

 * A timeout should be set before calling this routine.

 */

void ap_proxy_send_headers(request_rec *r, const char *respline, table *t)

{

    int i;

    BUFF *fp = r->connection->client;

    table_entry *elts = (table_entry *) ap_table_elts(t)->elts;



    ap_bputs(respline, fp);

    ap_bputs(CRLF, fp);



    for (i = 0; i < ap_table_elts(t)->nelts; ++i) {

	if (elts[i].key != NULL) {

	    ap_bvputs(fp, elts[i].key, ": ", elts[i].val, CRLF, NULL);

	    /* FIXME: @@@ This used to be ap_table_set(), but I think

	     * ap_table_addn() is correct. MnKr */

	    ap_table_addn(r->headers_out, elts[i].key, elts[i].val);

	}

    }



    ap_bputs(CRLF, fp);

}





