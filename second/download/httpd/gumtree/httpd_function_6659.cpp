static void H2_TASK_OUT_LOG(int lvl, h2_task *task, apr_bucket_brigade *bb, 
                            const char *tag)
{
    if (APLOG_C_IS_LEVEL(task->c, lvl)) {
        conn_rec *c = task->c;
        char buffer[4 * 1024];
        const char *line = "(null)";
        apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]);
        
        len = h2_util_bb_print(buffer, bmax, tag, "", bb);
        ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%s): %s", 
                      task->id, len? buffer : line);
    }
}