ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, 
                     "Failed to create shared memory segment on file %s", 
                     client_shm_filename);