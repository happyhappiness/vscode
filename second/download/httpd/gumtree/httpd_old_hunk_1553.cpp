	else
	    y[i] = ch + '0';
    }
    y[8] = '\0';
}

BUFF *
     ap_proxy_cache_error(struct cache_req *c)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, c->req->server,
		 "proxy: error writing to cache file %s", c->tempfile);
    ap_pclosef(c->req->pool, c->fp->fd);
    c->fp = NULL;
    unlink(c->tempfile);
    return NULL;
}
