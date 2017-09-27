ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03363)
                      "h2_proxy_session(%s): submit %s%s -> %d", 
                      session->id, stream->req->authority, stream->req->path,
                      rv);