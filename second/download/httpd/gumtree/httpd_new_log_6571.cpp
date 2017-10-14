ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, task->c,
                  "h2_task(%s): added chunk %ld, total %ld", 
                  task->id, (long)chunk_len, (long)task->input.chunked_total);