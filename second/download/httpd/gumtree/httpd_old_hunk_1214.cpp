		ap_proxy_send_headers(r, c->resp_line, c->hdrs);

		ap_kill_timeout(r);

	    }

	    ap_bsetopt(r->connection->client, BO_BYTECT, &zero);

	    r->sent_bodyct = 1;

	    if (!r->header_only)

		ap_proxy_send_fb(c->fp, r, NULL, NULL);

/* set any changed headers somehow */

/* update dates and version, but not content-length */

	    if (lmod != c->lmod || expc != c->expire || date != c->date) {

		off_t curpos = lseek(c->fp->fd, 0, SEEK_SET);



		if (curpos == -1)

		    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

				 "proxy: error seeking on cache file %s",

				 c->filename);

		else if (write(c->fp->fd, buff, 35) == -1)

		    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

				 "proxy: error updating cache file %s",

				 c->filename);

	    }

	    ap_pclosef(r->pool, c->fp->fd);

	    return OK;

	}

