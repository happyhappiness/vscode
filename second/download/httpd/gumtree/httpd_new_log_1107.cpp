ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init allocated %" APR_SIZE_T_FMT 
                 " bytes of shared memory",
                 shm_segsize);