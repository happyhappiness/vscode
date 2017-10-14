ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01261)
                      "daemon couldn't find CGI process for connection %lu",
                      r->connection->id);