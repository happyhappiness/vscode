static int h2_h2_late_fixups(request_rec *r)
{
    /* slave connection? */
    if (r->connection->master) {
        h2_ctx *ctx = h2_ctx_rget(r);
        struct h2_task *task = h2_ctx_get_task(ctx);
        if (task) {
            /* check if we copy vs. setaside files in this location */
            task->output.copy_files = h2_config_geti(h2_config_rget(r), 
                                                     H2_CONF_COPY_FILES);
            if (task->output.copy_files) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                              "h2_slave_out(%s): copy_files on", task->id);
                h2_beam_on_file_beam(task->output.beam, h2_beam_no_files, NULL);
            }
            check_push(r, "late_fixup");
        }
    }
    return DECLINED;
}