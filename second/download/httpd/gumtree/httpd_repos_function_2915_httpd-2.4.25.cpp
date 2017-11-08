static const char *set_doctype(cmd_parms *cmd, void *CFG,
                               const char *t, const char *l)
{
    proxy_html_conf *cfg = (proxy_html_conf *)CFG;
    if (!strcasecmp(t, "xhtml")) {
        cfg->etag = xhtml_etag;
        if (l && !strcasecmp(l, "legacy"))
            cfg->doctype = fpi_xhtml_legacy;
        else
            cfg->doctype = fpi_xhtml;
    }
    else if (!strcasecmp(t, "html")) {
        cfg->etag = html_etag;
        if (l && !strcasecmp(l, "legacy"))
            cfg->doctype = fpi_html_legacy;
        else
            cfg->doctype = fpi_html;
    }
    else {
        cfg->doctype = apr_pstrdup(cmd->pool, t);
        if (l && ((l[0] == 'x') || (l[0] == 'X')))
            cfg->etag = xhtml_etag;
        else
            cfg->etag = html_etag;
    }
    return NULL;
}