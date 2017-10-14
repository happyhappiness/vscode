ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03200)
                          "h2_session(%ld) created, max_streams=%d, "
                          "stream_mem=%d, workers_limit=%d, workers_max=%d, "
                          "push_diary(type=%d,N=%d)",
                          session->id, (int)session->max_stream_count, 
                          (int)session->max_stream_mem,
                          session->mplx->workers_limit, 
                          session->mplx->workers_max, 
                          session->push_diary->dtype, 
                          (int)session->push_diary->N);