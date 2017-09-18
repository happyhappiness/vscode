static const char *multiviews_match(cmd_parms *cmd, void *m_, 
                                    const char *include)
{
    mime_dir_config *m = (mime_dir_config *) m_;

    if (strcasecmp(include, "Any") == 0) {
        if (m->multimatch && (m->multimatch & ~MULTIMATCH_ANY))
            return "Any is incompatible with NegotiatedOnly, "
                   "Filters and Handlers";
        m->multimatch |= MULTIMATCH_ANY;
    }
    else if (strcasecmp(include, "NegotiatedOnly") == 0) {
        if (m->multimatch && (m->multimatch & ~MULTIMATCH_NEGOTIATED))
            return "Any is incompatible with NegotiatedOnly, "
                   "Filters and Handlers";
        m->multimatch |= MULTIMATCH_NEGOTIATED;
    }
    else if (strcasecmp(include, "Filters") == 0) {
        if (m->multimatch && (m->multimatch & (MULTIMATCH_NEGOTIATED 
                                             | MULTIMATCH_ANY)))
            return "Filters is incompatible with Any and NegotiatedOnly";
        m->multimatch |= MULTIMATCH_FILTERS;
    }
    else if (strcasecmp(include, "Handlers") == 0) {
        if (m->multimatch && (m->multimatch & (MULTIMATCH_NEGOTIATED 
                                             | MULTIMATCH_ANY)))
            return "Handlers is incompatible with Any and NegotiatedOnly";
        m->multimatch |= MULTIMATCH_HANDLERS;
    }
    else 
        return "Unrecognized option";

    return NULL;
}

static const command_rec mime_cmds[] =
{
AP_INIT_ITERATE2("AddCharset", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, charset_type), OR_FILEINFO,
     "a charset (e.g., iso-2022-jp), followed by one or more file extensions"),
AP_INIT_ITERATE2("AddEncoding", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, encoding_type), OR_FILEINFO,
     "an encoding (e.g., gzip), followed by one or more file extensions"),
AP_INIT_ITERATE2("AddHandler", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, handler), OR_FILEINFO,
     "a handler name followed by one or more file extensions"),
AP_INIT_ITERATE2("AddInputFilter", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, input_filters), OR_FILEINFO,
     "input filter name (or ; delimited names) followed by one or more file extensions"),
AP_INIT_ITERATE2("AddLanguage", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, language_type), OR_FILEINFO,
     "a language (e.g., fr), followed by one or more file extensions"),
AP_INIT_ITERATE2("AddOutputFilter", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, output_filters), OR_FILEINFO, 
     "output filter name (or ; delimited names) followed by one or more file extensions"),
AP_INIT_ITERATE2("AddType", add_extension_info, 
         (void *)APR_XtOffsetOf(extension_info, forced_type), OR_FILEINFO, 
     "a mime type followed by one or more file extensions"),
AP_INIT_TAKE1("DefaultLanguage", ap_set_string_slot,
       (void*)APR_XtOffsetOf(mime_dir_config, default_language), OR_FILEINFO,
     "language to use for documents with no other language file extension"),
AP_INIT_ITERATE("MultiviewsMatch", multiviews_match, NULL, OR_FILEINFO,
     "NegotiatedOnly (default), Handlers and/or Filters, or Any"),
AP_INIT_ITERATE("RemoveCharset", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, charset_type), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveEncoding", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, encoding_type), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveHandler", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, handler), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveInputFilter", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, input_filters), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveLanguage", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, language_type), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveOutputFilter", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, output_filters), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_ITERATE("RemoveType", remove_extension_info, 
        (void *)APR_XtOffsetOf(extension_info, forced_type), OR_FILEINFO,
     "one or more file extensions"),
AP_INIT_TAKE1("TypesConfig", set_types_config, NULL, RSRC_CONF,
     "the MIME types config file"),
    {NULL}
};

static apr_hash_t *mime_type_extensions;

static int mime_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    const char *types_confname = ap_get_module_config(s->module_config, &mime_module);
    apr_status_t status;

    if (!types_confname)
        types_confname = AP_TYPES_CONFIG_FILE;

    types_confname = ap_server_root_relative(p, types_confname);
    if (!types_confname) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
		     "Invalid mime types config path %s", 
                     (const char *)ap_get_module_config(s->module_config, &mime_module));
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if ((status = ap_pcfg_openfile(&f, ptemp, types_confname)) 
                != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
		     "could not open mime types config file %s.", 
