static int perchild_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    int i;
    server_rec *sr;
    perchild_server_conf *sconf;
    int def_sd[2];

    def_sd[0] = -1;
    def_sd[1] = -1;

    for (sr = s; sr; sr = sr->next) {
        sconf = (perchild_server_conf *)ap_get_module_config(sr->module_config,
                                                      &mpm_perchild_module);

        if (sconf->input == -1) {
            sconf->fullsockname = apr_pstrcat(sr->process->pool, 
                                             sconf->sockname, ".DEFAULT", NULL);
            if (def_sd[0] == -1) {
                if (!make_perchild_socket(sconf->fullsockname, def_sd)) {
                    /* log error */
                }
            }
            sconf->input = def_sd[0];
            sconf->output = def_sd[1];
        }
    }

    for (i = 0; i < num_daemons; i++) {
        if (child_info_table[i].uid == -1) {
            child_info_table[i].input = def_sd[0];
            child_info_table[i].output = def_sd[1];
        }
    }

    thread_socket_table = (int *)apr_pcalloc(p, thread_limit * sizeof(int));
    for (i = 0; i < thread_limit; i++) {
        thread_socket_table[i] = AP_PERCHILD_THISCHILD;
    }
    ap_child_table = (ap_ctable *)apr_pcalloc(p, server_limit * sizeof(ap_ctable));

    return OK;
}