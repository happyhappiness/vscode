		format = apr_table_get(mls->formats, cls->format_string);
		if (format) {
		    cls->format = parse_log_string(p, format, &dummy);
		}
	    }

            if (!open_config_log(s, p, cls, mls->default_format)) {
                /* Failure already logged by open_config_log */
                return DONE;
            }
        }
    }

    return OK;
}


static apr_status_t flush_all_logs(void *data)
{
    server_rec *s = data;
    multi_log_state *mls;
    apr_array_header_t *log_list;
    config_log_state *clsarray;
    buffered_log *buf;
    int i;

    if (!buffered_logs)
        return APR_SUCCESS;
    
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
                buf = clsarray[i].log_writer;
                flush_log(buf);
            }
        }
    }
    return APR_SUCCESS;
}


static int init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
{
    /* First, do "physical" server, which gets default log fd and format
     * for the virtual servers, if they don't override...
     */
    int res = open_multi_logs(s, p);

    /* Then, virtual servers */

    for (s = s->next; (res == OK) && s; s = s->next) {
        res = open_multi_logs(s, p);
    }

    return res;
}

static void init_child(apr_pool_t *p, server_rec *s)
{
	/* Now register the last buffer flush with the cleanup engine */
    if (buffered_logs)
	    apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
}

static void ap_register_log_handler(apr_pool_t *p, char *tag, 
                                    ap_log_handler_fn_t *handler, int def)
{
    ap_log_handler *log_struct = apr_palloc(p, sizeof(*log_struct));
    log_struct->func = handler;
    log_struct->want_orig_default = def;

    apr_hash_set(log_hash, tag, 1, (const void *)log_struct);
}
static void ap_log_set_writer_init(ap_log_writer_init *handle)
{
    log_writer_init = handle;

}
static void ap_log_set_writer(ap_log_writer *handle)
{
    log_writer = handle;
}

static apr_status_t ap_default_log_writer( request_rec *r,
                           void *handle, 
                           const char **strs,
                           int *strl,
                           int nelts,
                           apr_size_t len)

{
    char *str;
    char *s;
    int i;
    apr_status_t rv;

    str = apr_palloc(r->pool, len + 1);

    for (i = 0, s = str; i < nelts; ++i) {
        memcpy(s, strs[i], strl[i]);
        s += strl[i];
    }

    rv = apr_file_write((apr_file_t*)handle, str, &len);

    return rv;
}
static void *ap_default_log_writer_init(apr_pool_t *p, server_rec *s, 
                                        const char* name)
{
    if (*name == '|') {
        piped_log *pl;

        pl = ap_open_piped_log(p, name + 1);
        if (pl == NULL) {
           return NULL;;
        }
        return ap_piped_log_write_fd(pl);
    }
    else {
        const char *fname = ap_server_root_relative(p, name);
        apr_file_t *fd;
        apr_status_t rv;

        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                            "invalid transfer log path %s.", name);
            return NULL;
        }
        rv = apr_file_open(&fd, fname, xfer_flags, xfer_perms, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                            "could not open transfer log file %s.", fname);
            return NULL;
        }
        apr_file_inherit_set(fd);
        return fd;
    }
}
static void *ap_buffered_log_writer_init(apr_pool_t *p, server_rec *s, 
                                        const char* name)
{
    buffered_log *b;
    b = apr_palloc(p, sizeof(buffered_log));
    b->handle = ap_default_log_writer_init(p, s, name);
    b->outcnt = 0;
    
    if (b->handle)
        return b;
    else
        return NULL;
}
static apr_status_t ap_buffered_log_writer(request_rec *r,
                                           void *handle, 
                                           const char **strs,
                                           int *strl,
                                           int nelts,
                                           apr_size_t len)

{
    char *str;
    char *s;
    int i;
    apr_status_t rv;
    buffered_log *buf = (buffered_log*)handle;


    if (len + buf->outcnt > LOG_BUFSIZE) {
        flush_log(buf);
    }
    if (len >= LOG_BUFSIZE) {
        apr_size_t w;

        str = apr_palloc(r->pool, len + 1);
        for (i = 0, s = str; i < nelts; ++i) {
            memcpy(s, strs[i], strl[i]);
            s += strl[i];
        }
        w = len;
        rv = apr_file_write(buf->handle, str, &w);
        
    }
    else {
        for (i = 0, s = &buf->outbuf[buf->outcnt]; i < nelts; ++i) {
            memcpy(s, strs[i], strl[i]);
            s += strl[i];
        }
        buf->outcnt += len;
        rv = APR_SUCCESS;
    }
    return rv;
}

static int log_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static APR_OPTIONAL_FN_TYPE(ap_register_log_handler) *log_pfn_register;
    
    log_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_log_handler);

    if (log_pfn_register) {
        log_pfn_register(p, "h", log_remote_host, 0);
        log_pfn_register(p, "a", log_remote_address, 0 );
        log_pfn_register(p, "A", log_local_address, 0 );
