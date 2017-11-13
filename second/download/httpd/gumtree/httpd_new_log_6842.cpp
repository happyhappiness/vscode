ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
                      H2_SSSN_LOG(APLOGNO(03200), session, 
                                  "created, max_streams=%d, stream_mem=%d, "
                                  "workers_limit=%d, workers_max=%d, "
                                  "push_diary(type=%d,N=%d)"),
                      (int)session->max_stream_count, 
                      (int)session->max_stream_mem,
                      session->mplx->limit_active, 
                      session->mplx->max_active, 
                      session->push_diary->dtype, 
                      (int)session->push_diary->N);