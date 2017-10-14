ap_log_cerror(APLOG_MARK, APLOG_ERR, status, master, 
                      APLOGNO(10004) "h2_session(%ld-%d): create slave pool",
                      master->id, slave_id);