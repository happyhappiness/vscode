	    n = strlen(buf);
	}

	o = 0;
	total_bytes_sent += n;

	if (f2 != NULL)
	    if (ap_bwrite(f2, buf, n) != n)
		f2 = ap_proxy_cache_error(c);

	while (n && !r->connection->aborted) {
	    w = ap_bwrite(con->client, &buf[o], n);
	    if (w <= 0)
		break;
	    ap_reset_timeout(r);	/* reset timeout after successfule write */
	    n -= w;
	    o += w;
	}
    }
    site = "</PRE><HR>\n";
    ap_bputs(site, con->client);
    if (f2 != NULL)
	ap_bputs(site, f2);
    total_bytes_sent += strlen(site);

    sig = ap_psignature("", r);
    ap_bputs(sig, con->client);
    if (f2 != NULL)
	ap_bputs(sig, f2);
    total_bytes_sent += strlen(sig);

    site = "</BODY></HTML>\n";
    ap_bputs(site, con->client);
    if (f2 != NULL)
	ap_bputs(site, f2);
    total_bytes_sent += strlen(site);
    ap_bflush(con->client);

    return total_bytes_sent;
}

/*
 * Handles direct access of ftp:// URLs
 * Original (Non-PASV) version from
 * Troy Morrison <spiffnet@zoom.com>
 * PASV added by Chuck
 */
int ap_proxy_ftp_handler(request_rec *r, struct cache_req *c, char *url)
{
    char *host, *path, *strp, *user, *password, *parms;
    const char *err;
    int port, userlen, i, j, len, sock, dsock, rc, nocache;
    int passlen = 0;
    int csd = 0;
    struct sockaddr_in server;
    struct hostent server_hp;
    struct hdr_entry *hdr;
    struct in_addr destaddr;
    array_header *resp_hdrs;
    BUFF *f, *cache;
    BUFF *data = NULL;
    pool *p = r->pool;
    int one = 1;
    const long int zero = 0L;
    NET_SIZE_T clen;

    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    struct noproxy_entry *npent = (struct noproxy_entry *) conf->noproxies->elts;
    struct nocache_entry *ncent = (struct nocache_entry *) conf->nocaches->elts;
