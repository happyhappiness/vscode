            apr_file_printf(out, "Define: %s=%s\n", name, val);
        else
            apr_file_printf(out, "Define: %s\n", name);
    }
}

static void register_hooks(apr_pool_t *p)
{
    errorlog_hash = apr_hash_make(p);
    ap_register_log_hooks(p);
    ap_register_config_hooks(p);
    ap_expr_init(p);
