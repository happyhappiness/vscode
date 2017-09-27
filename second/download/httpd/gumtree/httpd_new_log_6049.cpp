ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_task_input(%s): read, block=%d, mode=%d, readbytes=%ld", 
                  input->task->id, block, mode, (long)readbytes);