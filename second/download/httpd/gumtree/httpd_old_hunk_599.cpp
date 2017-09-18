	    s, apr_strerror(rv, buf, sizeof buf), rv);
    if (done)
        printf("Total of %ld requests completed\n" , done);
    exit(rv);
}

/* --------------------------------------------------------- */
/* write out request to a connection - assumes we can write
 * (small) request out in one go into our new socket buffer
 *
 */
static void write_request(struct connection * c)
{
    do {
	apr_time_t tnow = apr_time_now();
	apr_size_t l = c->rwrite;
	apr_status_t e;

	/*
	 * First time round ?
	 */
	if (c->rwrite == 0) {
	    apr_setsocketopt(c->aprsock, APR_SO_TIMEOUT, 0);
	    c->connect = tnow;
	    c->rwrite = reqlen;
	    c->rwrote = 0;
	    if (posting)
		c->rwrite += postlen;
