ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
                          "h2_mplx(%ld): release_join -> destroy, "
                          "%d tasks still present", 
                          m->id, (int)h2_ihash_count(m->tasks));