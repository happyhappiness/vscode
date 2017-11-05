ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00822)
                 "for %" APR_SIZE_T_FMT " bytes (%" APR_SIZE_T_FMT
                 " including header), recommending %u subcaches, "
                 "%u indexes each", shm_segsize,
                 shm_segsize + sizeof(SHMCBHeader), num_subcache, num_idx);