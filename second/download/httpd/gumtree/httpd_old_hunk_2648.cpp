                     *   Hopefully it will not be needed.
                     * . It is not possible to noop an instance which has
                     *   already run.
                     */
                    if (last_xlate_ctx == f->ctx) {
                        last_xlate_ctx->noop = 1;
                        if (debug >= DBGLVL_PMC) {
                            const char *symbol = output ? "->" : "<-";

                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                          0, f->r,
                                          "%s %s - disabling "
                                          "translation %s%s%s; existing "
                                          "translation %s%s%s",
                                          f->r->uri ? "uri" : "file",
                                          f->r->uri ? f->r->uri : f->r->filename,
                                          last_xlate_ctx->dc->charset_source,
