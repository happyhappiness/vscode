static int cgi_handler(request_rec *r)
{
    int nph;
    apr_size_t dbpos = 0;
    const char *argv0;
    const char *command;
    const char **argv;
    char *dbuf = NULL;
    apr_file_t *script_out = NULL, *script_in = NULL, *script_err = NULL;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    int is_included;
    int seen_eos, child_stopped_reading;
    apr_pool_t *p;
    cgi_server_conf *conf;
    apr_status_t rv;
    cgi_exec_info_t e_info;
    conn_rec *c = r->connection;

    if(strcmp(r->handler, CGI_MAGIC_TYPE) && strcmp(r->handler, "cgi-script"))
        return DECLINED;

    is_included = !strcmp(r->protocol, "INCLUDED");

    p = r->main ? r->main->pool : r->pool;

    argv0 = apr_filename_of_pathname(r->filename);
    nph = !(strncmp(argv0, "nph-", 4));
    conf = ap_get_module_config(r->server->module_config, &cgi_module);

    if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r))
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "Options ExecCGI is off in this directory");
    if (nph && is_included)
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "attempt to include NPH CGI script");

    if (r->finfo.filetype == 0)
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                               "script not found or unable to stat");
    if (r->finfo.filetype == APR_DIR)
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "attempt to invoke directory as script");

    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info)
    {
        /* default to accept */
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                               "AcceptPathInfo off disallows user's path");
    }
/*
    if (!ap_suexec_enabled) {
        if (!ap_can_exec(&r->finfo))
            return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                   "file permissions deny server execution");
    }

*/
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    e_info.process_cgi = 1;
    e_info.cmd_type    = APR_PROGRAM;
    e_info.detached    = 0;
    e_info.in_pipe     = APR_CHILD_BLOCK;
    e_info.out_pipe    = APR_CHILD_BLOCK;
    e_info.err_pipe    = APR_CHILD_BLOCK;
    e_info.prog_type   = RUN_AS_CGI;
    e_info.bb          = NULL;
    e_info.ctx         = NULL;
    e_info.next        = NULL;

    /* build the command line */
    if ((rv = cgi_build_command(&command, &argv, r, p, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn child process: %s", 
                      r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, p, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "couldn't spawn child process: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Transfer any put/post args, CERN style...
     * Note that we already ignore SIGPIPE in the core server.
     */
    bb = apr_brigade_create(r->pool, c->bucket_alloc);
    seen_eos = 0;
    child_stopped_reading = 0;
    if (conf->logname) {
        dbuf = apr_palloc(r->pool, conf->bufbytes + 1);
        dbpos = 0;
    }
    do {
        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);
       
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Error reading request entity data");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        APR_BRIGADE_FOREACH(bucket, bb) {
            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }

            /* We can't do much with this. */
            if (APR_BUCKET_IS_FLUSH(bucket)) {
                continue;
            }

            /* If the child stopped, we still must read to EOS. */
            if (child_stopped_reading) {
                continue;
            } 

            /* read */
            apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
            
            if (conf->logname && dbpos < conf->bufbytes) {
                int cursize;

                if ((dbpos + len) > conf->bufbytes) {
                    cursize = conf->bufbytes - dbpos;
                }
                else {
                    cursize = len;
                }
                memcpy(dbuf + dbpos, data, cursize);
                dbpos += cursize;
            }

            /* Keep writing data to the child until done or too much time
             * elapses with no progress or an error occurs.
             */
            rv = apr_file_write_full(script_out, data, len, NULL);

            if (rv != APR_SUCCESS) {
                /* silly script stopped reading, soak up remaining message */
                child_stopped_reading = 1;
            }
        }
        apr_brigade_cleanup(bb);
    }
    while (!seen_eos);

    if (conf->logname) {
        dbuf[dbpos] = '\0';
    }
    /* Is this flush really needed? */
    apr_file_flush(script_out);
    apr_file_close(script_out);

    AP_DEBUG_ASSERT(script_in != NULL);

    apr_brigade_cleanup(bb);

#if APR_FILES_AS_SOCKETS
    apr_file_pipe_timeout_set(script_in, 0);
    apr_file_pipe_timeout_set(script_err, 0);
    
    b = cgi_bucket_create(r, script_in, script_err, c->bucket_alloc);
#else
    b = apr_bucket_pipe_create(script_in, c->bucket_alloc);
#endif
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    /* Handle script return... */
    if (!nph) {
        const char *location;
        char sbuf[MAX_STRING_LEN];
        int ret;

        if ((ret = ap_scan_script_header_err_brigade(r, bb, sbuf))) {
            return log_script(r, conf, ret, dbuf, sbuf, bb, script_err);
        }

        location = apr_table_get(r->headers_out, "Location");

        if (location && location[0] == '/' && r->status == 200) {
            discard_script_output(bb);
            apr_brigade_destroy(bb);
            apr_file_pipe_timeout_set(script_err, r->server->timeout);
            log_script_err(r, script_err);
            /* This redirect needs to be a GET no matter what the original
             * method was.
             */
            r->method = apr_pstrdup(r->pool, "GET");
            r->method_number = M_GET;

            /* We already read the message body (if any), so don't allow
             * the redirected request to think it has one.  We can ignore 
             * Transfer-Encoding, since we used REQUEST_CHUNKED_ERROR.
             */
            apr_table_unset(r->headers_in, "Content-Length");

            ap_internal_redirect_handler(location, r);
            return OK;
        }
        else if (location && r->status == 200) {
            /* XX Note that if a script wants to produce its own Redirect
             * body, it now has to explicitly *say* "Status: 302"
             */
            discard_script_output(bb);
            apr_brigade_destroy(bb);
            return HTTP_MOVED_TEMPORARILY;
        }

        rv = ap_pass_brigade(r->output_filters, bb);
    }
    else /* nph */ {
        struct ap_filter_t *cur;
        
        /* get rid of all filters up through protocol...  since we
         * haven't parsed off the headers, there is no way they can
         * work
         */

        cur = r->proto_output_filters;
        while (cur && cur->frec->ftype < AP_FTYPE_CONNECTION) {
            cur = cur->next;
        }
        r->output_filters = r->proto_output_filters = cur;

        rv = ap_pass_brigade(r->output_filters, bb);
    }

    /* don't soak up script output if errors occurred writing it
     * out...  otherwise, we prolong the life of the script when the
     * connection drops or we stopped sending output for some other
     * reason */
    if (rv == APR_SUCCESS && !r->connection->aborted) {
        apr_file_pipe_timeout_set(script_err, r->server->timeout);
        log_script_err(r, script_err);
    }
    
    apr_file_close(script_err);

    return OK;                      /* NOT r->status, even if it has changed. */
}