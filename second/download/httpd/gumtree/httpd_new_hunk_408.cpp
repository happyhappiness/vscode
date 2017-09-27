        return ap_pass_brigade(f->next, bb);
    }

    apr_table_unset(r->headers_out, "Upgrade");

    if (r) {
        csd_data = (secsocket_data*)ap_get_module_config(r->connection->conn_config, &nwssl_module);
        csd = csd_data->csd;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Unable to get upgradeable socket handle");
        return ap_pass_brigade(f->next, bb);
    }
