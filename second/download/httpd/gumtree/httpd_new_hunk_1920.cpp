	return DECLINED;



    Explain1("Create temporary file %s", c->tempfile);



    i = open(c->tempfile, O_WRONLY | O_CREAT | O_EXCL | O_BINARY, 0622);

    if (i == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy: error creating cache file %s",

		     c->tempfile);

	return DECLINED;

    }

    ap_note_cleanups_for_fd(r->pool, i);

    c->fp = ap_bcreate(r->pool, B_WR);

    ap_bpushfd(c->fp, -1, i);



    if (ap_bvputs(c->fp, buff, "X-URL: ", c->url, "\n", NULL) == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy: error writing cache file(%s)", c->tempfile);

	ap_pclosef(r->pool, c->fp->fd);

	unlink(c->tempfile);

	c->fp = NULL;

    }

    return DECLINED;

}



void ap_proxy_cache_tidy(cache_req *c)

{

    server_rec *s;

    long int bc;



    if (c == NULL || c->fp == NULL)

	return;



    s = c->req->server;



/* don't care how much was sent, but rather how much was written to cache

    ap_bgetopt(c->req->connection->client, BO_BYTECT, &bc);

 */

    bc = c->written;



    if (c->len != -1) {

