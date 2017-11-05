static int perchild_post_read(request_rec *r)
{
    int thread_num = r->connection->id % thread_limit;
    perchild_server_conf *sconf = (perchild_server_conf *)
                            ap_get_module_config(r->server->module_config, 
                                                 &mpm_perchild_module);

    if (thread_socket_table[thread_num] != AP_PERCHILD_THISCHILD) {
        apr_socket_t *csd = NULL;

        apr_os_sock_put(&csd, &thread_socket_table[thread_num], 
                        r->connection->pool);
        ap_sock_disable_nagle(csd);
        ap_set_module_config(r->connection->conn_config, &core_module, csd);
        return OK;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                     "Determining if request should be passed. "
                     "Child Num: %d, SD: %d, sd from table: %d, hostname from server: %s", child_num, 
                     sconf->sd, child_info_table[child_num].sd, 
                     r->server->server_hostname);
        /* sconf is the server config for this vhost, so if our socket
         * is not the same that was set in the config, then the request
         * needs to be passed to another child. */
        if (sconf->sd != child_info_table[child_num].sd) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                         "Passing request.");
            if (pass_request(r) == -1) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             ap_server_conf, "Could not pass request to proper "
                             "child, request will not be honored.");
            }
            longjmp(jmpbuffer, 1); 
        }
        return OK;
    }
    return OK;
}