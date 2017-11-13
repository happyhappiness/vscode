static const char *
    set_proxy_dirconn(cmd_parms *parms, void *dummy, const char *arg)
{
    server_rec *s = parms->server;
    proxy_server_conf *conf =
    ap_get_module_config(s->module_config, &proxy_module);
    struct dirconn_entry *New;
    struct dirconn_entry *list = (struct dirconn_entry *) conf->dirconn->elts;
    int found = 0;
    int i;

    /* Don't duplicate entries */
    for (i = 0; i < conf->dirconn->nelts; i++) {
        if (strcasecmp(arg, list[i].name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        New = apr_array_push(conf->dirconn);
        New->name = apr_pstrdup(parms->pool, arg);
        New->hostaddr = NULL;

        if (ap_proxy_is_ipaddr(New, parms->pool)) {
#if DEBUGGING
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "Parsed addr %s", inet_ntoa(New->addr));
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "Parsed mask %s", inet_ntoa(New->mask));
#endif
        }
        else if (ap_proxy_is_domainname(New, parms->pool)) {
            ap_str_tolower(New->name);
#if DEBUGGING
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "Parsed domain %s", New->name);
#endif
        }
        else if (ap_proxy_is_hostname(New, parms->pool)) {
            ap_str_tolower(New->name);
#if DEBUGGING
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "Parsed host %s", New->name);
#endif
        }
        else {
            ap_proxy_is_word(New, parms->pool);
#if DEBUGGING
            fprintf(stderr, "Parsed word %s\n", New->name);
#endif
        }
    }
    return NULL;
}