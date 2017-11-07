ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOTIMPL, f->c,
                      APLOGNO(03472) 
                      "h2_slave_in(%s), unsupported READ mode %d", 
                      task->id, mode);