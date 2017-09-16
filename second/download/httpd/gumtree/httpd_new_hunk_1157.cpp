#ifdef WIN32

	if (i == SOCKET_ERROR)

	    errno = WSAGetLastError();

#endif /* WIN32 */

    } while (i == -1 && errno == EINTR);

    if (i == -1) {

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "proxy connect to %s port %d failed",

		     inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));

    }

    ap_kill_timeout(r);



    return i;

}



/* This function is called by ap_table_do() for all header lines */

/* (from proxy_http.c and proxy_ftp.c) */

/* It is passed a table_do_args struct pointer and a MIME field and value pair */

int ap_proxy_send_hdr_line(void *p, const char *key, const char *value)

{

    struct tbl_do_args *parm = (struct tbl_do_args *)p;



    if (key == NULL || value == NULL || value[0] == '\0')

	return 1;

    if (!parm->req->assbackwards)

	ap_rvputs(parm->req, key, ": ", value, CRLF, NULL);

    if (parm->cache != NULL && parm->cache->fp != NULL &&

	ap_bvputs(parm->cache->fp, key, ": ", value, CRLF, NULL) == -1)

	    parm->cache = ap_proxy_cache_error(parm->cache);

    return 1; /* tell ap_table_do() to continue calling us for more headers */

}



/* send a text line to one or two BUFF's; return line length */

unsigned ap_proxy_bputs2(const char *data, BUFF *client, cache_req *cache)

{

    unsigned len = ap_bputs(data, client);

    if (cache != NULL && cache->fp != NULL)

	ap_bputs(data, cache->fp);

    return len;

}



