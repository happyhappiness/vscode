    if (conf->limit_xml_body < 0)
        return "LimitXMLRequestBody requires a non-negative integer.";

    return NULL;
}

AP_DECLARE(size_t) ap_get_limit_xml_body(const request_rec *r)
{
    core_dir_config *conf;

    conf = ap_get_module_config(r->per_dir_config, &core_module);
    if (conf->limit_xml_body == AP_LIMIT_UNSET)
        return AP_DEFAULT_LIMIT_XML_BODY;

    return (size_t)conf->limit_xml_body;
}

#if !defined (RLIMIT_CPU) || !(defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined(RLIMIT_AS)) || !defined (RLIMIT_NPROC)
static const char *no_set_limit(cmd_parms *cmd, void *conf_,
                                const char *arg, const char *arg2)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
                "%s not supported on this platform", cmd->cmd->name);

    return NULL;
}
#endif

