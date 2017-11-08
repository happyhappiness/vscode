static int nwssl_pre_connection(conn_rec *c, void *csd)
{

    if (apr_table_get(c->notes, "nwconv-ssl")) {
        convert_secure_socket(c, (apr_socket_t*)csd);
    }
    else {
        secsocket_data *csd_data = apr_palloc(c->pool, sizeof(secsocket_data));

        csd_data->csd = (apr_socket_t*)csd;
        csd_data->is_secure = 0;
        ap_set_module_config(c->conn_config, &nwssl_module, (void*)csd_data);
    }

    return OK;
}