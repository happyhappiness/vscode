		format = apr_table_get(mls->formats, cls->format_string);
		if (format) {
		    cls->format = parse_log_string(p, format, &dummy);
		}
	    }

            cls = open_config_log(s, p, cls, mls->default_format);
        }
    }

    return NULL;
}

#ifdef BUFFERED_LOGS
static apr_status_t flush_all_logs(void *data)
{
    server_rec *s = data;
    multi_log_state *mls;
    apr_array_header_t *log_list;
    config_log_state *clsarray;
    int i;

    for (; s; s = s->next) {
        mls = ap_get_module_config(s->module_config, &log_config_module);
        log_list = NULL;
        if (mls->config_logs->nelts) {
            log_list = mls->config_logs;
        }
        else if (mls->server_config_logs) {
            log_list = mls->server_config_logs;
        }
        if (log_list) {
            clsarray = (config_log_state *) log_list->elts;
            for (i = 0; i < log_list->nelts; ++i) {
                flush_log(&clsarray[i]);
            }
        }
    }
    return APR_SUCCESS;
}
#endif

static int init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
{
    /* First, do "physical" server, which gets default log fd and format
     * for the virtual servers, if they don't override...
     */

    open_multi_logs(s, p);

    /* Then, virtual servers */

    for (s = s->next; s; s = s->next) {
        open_multi_logs(s, p);
    }
    return OK;
}

static void init_child(apr_pool_t *p, server_rec *s)
{
#ifdef BUFFERED_LOGS
	/* Now register the last buffer flush with the cleanup engine */
	apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
#endif
}

static void ap_register_log_handler(apr_pool_t *p, char *tag, 
                                    ap_log_handler_fn_t *handler, int def)
{
    ap_log_handler *log_struct = apr_palloc(p, sizeof(*log_struct));
    log_struct->func = handler;
    log_struct->want_orig_default = def;

    apr_hash_set(log_hash, tag, 1, (const void *)log_struct);
}

static int log_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static APR_OPTIONAL_FN_TYPE(ap_register_log_handler) *log_pfn_register;

    log_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_log_handler);

    if (log_pfn_register) {
        log_pfn_register(p, "h", log_remote_host, 0);
        log_pfn_register(p, "a", log_remote_address, 0 );
        log_pfn_register(p, "A", log_local_address, 0 );
