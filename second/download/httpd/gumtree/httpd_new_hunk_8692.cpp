	    n = strlen(buf);
	}

	o = 0;
	total_bytes_sent += n;

	if (c != NULL && c->fp && ap_bwrite(c->fp, buf, n) != n)
	    c = ap_proxy_cache_error(c);

	while (n && !r->connection->aborted) {
	    w = ap_bwrite(con->client, &buf[o], n);
	    if (w <= 0)
		break;
	    ap_reset_timeout(r);	/* reset timeout after successfule write */
	    n -= w;
	    o += w;
	}
    }

    total_bytes_sent += ap_proxy_bputs2("</PRE><HR>\n", con->client, c);
    total_bytes_sent += ap_proxy_bputs2(ap_psignature("", r), con->client, c);
    total_bytes_sent += ap_proxy_bputs2("</BODY></HTML>\n", con->client, c);

    ap_bflush(con->client);

    return total_bytes_sent;
}

/* Common routine for failed authorization (i.e., missing or wrong password)
 * to an ftp service. This causes most browsers to retry the request
 * with username and password (which was presumably queried from the user)
 * supplied in the Authorization: header.
 * Note that we "invent" a realm name which consists of the
 * ftp://user@host part of the reqest (sans password -if supplied but invalid-)
 */
static int ftp_unauthorized (request_rec *r, int log_it)
{
    r->proxyreq = 0;
    /* Log failed requests if they supplied a password
     * (log username/password guessing attempts)
     */
    if (log_it)
	ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, r,
		      "proxy: missing or failed auth to %s",
		      ap_unparse_uri_components(r->pool,
		      &r->parsed_uri, UNP_OMITPATHINFO));

    ap_table_setn(r->err_headers_out, "WWW-Authenticate",
                  ap_pstrcat(r->pool, "Basic realm=\"",
		  ap_unparse_uri_components(r->pool, &r->parsed_uri,
					    UNP_OMITPASSWORD|UNP_OMITPATHINFO),
		  "\"", NULL));

    return HTTP_UNAUTHORIZED;
}

/*
 * Handles direct access of ftp:// URLs
 * Original (Non-PASV) version from
 * Troy Morrison <spiffnet@zoom.com>
 * PASV added by Chuck
 */
int ap_proxy_ftp_handler(request_rec *r, cache_req *c, char *url)
{
    char *host, *path, *strp, *parms;
    char *cwd = NULL;
    char *user = NULL;
/*    char *account = NULL; how to supply an account in a URL? */
    const char *password = NULL;
    const char *err;
    int port, i, j, len, sock, dsock, rc, nocache = 0;
    int csd = 0;
    struct sockaddr_in server;
    struct hostent server_hp;
    struct in_addr destaddr;
    table *resp_hdrs;
    BUFF *f;
    BUFF *data = NULL;
    pool *p = r->pool;
    int one = 1;
    const long int zero = 0L;
    NET_SIZE_T clen;
    struct tbl_do_args tdo;

    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
    struct nocache_entry *ncent = (struct nocache_entry *) conf->nocaches->elts;
