                                            c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
	    ap_pass_brigade(cid->r->output_filters, bb);
        }
        return TRUE;

    }
#endif

    case 1017: /* HSE_REQ_CLOSE_CONNECTION  Added after ISAPI 4.0 */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction "
                          "HSE_REQ_CLOSE_CONNECTION "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

    case 1018: /* HSE_REQ_IS_CONNECTED  Added after ISAPI 4.0 */
        /* Returns True if client is connected c.f. MSKB Q188346
         * assuming the identical return mechanism as HSE_REQ_IS_KEEP_CONN
         */
        *((LPBOOL) lpvBuffer) = (r->connection->aborted == 0);
        return TRUE;

    case 1020: /* HSE_REQ_EXTENSION_TRIGGER  Added after ISAPI 4.0 */
        /*  Undocumented - defined by the Microsoft Jan '00 Platform SDK
         */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction "
                          "HSE_REQ_EXTENSION_TRIGGER "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

    default:
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction (%d) not supported: "
                          "%s", dwHSERequest, r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }
}

/*
 * Command handler for the ISAPIReadAheadBuffer directive, which is TAKE1
 */
static const char *isapi_cmd_readaheadbuffer(cmd_parms *cmd, void *config, 
                                             char *arg)
{
    isapi_server_conf *sconf = ap_get_module_config(cmd->server->module_config,
                                                   &isapi_module);
    char *scan;
    long val;

    if (((val = strtol(arg, (char **) &scan, 10)) <= 0) || *scan)
        return "ISAPIReadAheadBuffer must be a legitimate value.";
    
    sconf->ReadAheadBuffer = val;
    return NULL;
}

/*
 * Command handler for the ISAPIReadAheadBuffer directive, which is TAKE1
 */
static const char *isapi_cmd_lognotsupported(cmd_parms *cmd, void *config, 
                                             char *arg)
{
    isapi_server_conf *sconf = ap_get_module_config(cmd->server->module_config,
                                               &isapi_module);

    if (strcasecmp(arg, "on") == 0) {
        sconf->LogNotSupported = -1;
    }
    else if (strcasecmp(arg, "off") == 0) {
        sconf->LogNotSupported = 0;
    }
    else {
        return "ISAPILogNotSupported must be on or off";
    }
    return NULL;
}

static const char *isapi_cmd_appendlogtoerrors(cmd_parms *cmd, void *config, 
                                               char *arg)
{
    isapi_server_conf *sconf = ap_get_module_config(cmd->server->module_config,
                                                   &isapi_module);

    if (strcasecmp(arg, "on") == 0) {
        sconf->AppendLogToErrors = -1;
    }
    else if (strcasecmp(arg, "off") == 0) {
        sconf->AppendLogToErrors = 0;
    }
    else {
        return "ISAPIAppendLogToErrors must be on or off";
    }
    return NULL;
}

static const char *isapi_cmd_appendlogtoquery(cmd_parms *cmd, void *config, 
                                              char *arg)
{
    isapi_server_conf *sconf = ap_get_module_config(cmd->server->module_config,
                                                   &isapi_module);

    if (strcasecmp(arg, "on") == 0) {
        sconf->AppendLogToQuery = -1;
    }
    else if (strcasecmp(arg, "off") == 0) {
        sconf->AppendLogToQuery = 0;
    }
    else {
        return "ISAPIAppendLogToQuery must be on or off";
    }
    return NULL;
}

static const char *isapi_cmd_cachefile(cmd_parms *cmd, void *dummy, 
                                       const char *filename)

{
    isapi_server_conf *sconf = ap_get_module_config(cmd->server->module_config, 
                                                    &isapi_module);
    isapi_loaded *isa, **newisa;
    apr_finfo_t tmp;
    apr_status_t rv;
    char *fspec;
    
    fspec = ap_server_root_relative(cmd->pool, filename);
    if (!fspec) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
	             "ISAPI: Invalid module path %s, skipping", filename);
	return NULL;
    }
    if ((rv = apr_stat(&tmp, fspec, APR_FINFO_TYPE, 
                      cmd->temp_pool)) != APR_SUCCESS) { 
	ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
	    "ISAPI: unable to stat(%s), skipping", fspec);
	return NULL;
    }
    if (tmp.filetype != APR_REG) {
	ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, cmd->server,
	    "ISAPI: %s isn't a regular file, skipping", fspec);
	return NULL;
    }

    /* Load the extention as cached (passing sconf) */
    rv = isapi_load(cmd->pool, sconf, NULL, fspec, &isa); 
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server,
                     "ISAPI: unable to cache %s, skipping", fspec);
	return NULL;
    }

    /* Add to cached list of loaded modules */
    newisa = apr_array_push(sconf->loaded);
    *newisa = isa;
    
    return NULL;
}

static void isapi_hooks(apr_pool_t *cont)
{
    ap_hook_post_config(isapi_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(isapi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

static const command_rec isapi_cmds[] = {
AP_INIT_TAKE1("ISAPIReadAheadBuffer", isapi_cmd_readaheadbuffer, NULL, RSRC_CONF,
  "Maximum bytes to initially pass to the ISAPI handler"),
AP_INIT_TAKE1("ISAPILogNotSupported", isapi_cmd_lognotsupported, NULL, RSRC_CONF,
  "Log requests not supported by the ISAPI server"),
AP_INIT_TAKE1("ISAPIAppendLogToErrors", isapi_cmd_appendlogtoerrors, NULL, RSRC_CONF,
  "Send all Append Log requests to the error log"),
AP_INIT_TAKE1("ISAPIAppendLogToQuery", isapi_cmd_appendlogtoquery, NULL, RSRC_CONF,
  "Append Log requests are concatinated to the query args"),
AP_INIT_ITERATE("ISAPICacheFile", isapi_cmd_cachefile, NULL, RSRC_CONF,
  "Cache the specified ISAPI extension in-process"),
{ NULL }
};

module AP_MODULE_DECLARE_DATA isapi_module = {
   STANDARD20_MODULE_STUFF,
   NULL,                        /* create per-dir config */
   NULL,                        /* merge per-dir config */
   create_isapi_server_config,  /* server config */
   NULL,                        /* merge server config */
   isapi_cmds,                  /* command apr_table_t */
   isapi_hooks                  /* register hooks */
};
