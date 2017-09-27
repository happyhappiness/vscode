ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, master, 
                      APLOGNO(02913) "h2_session(%ld-%d): create slave",
                      master->id, slave_id);