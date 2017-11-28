static ErrorDynamicPageInfo *
errorDynamicPageInfoCreate(int id, const char *page_name)
{
    ErrorDynamicPageInfo *info = new ErrorDynamicPageInfo;
    info->id = id;
    info->page_name = xstrdup(page_name);
    info->page_redirect = static_cast<http_status>(atoi(page_name));

    /* WARNING on redirection status:
     * 2xx are permitted, but not documented officially.
     * - might be useful for serving static files (PAC etc) in special cases
     * 3xx require a URL suitable for Location: header.
     * - the current design does not allow for a Location: URI as well as a local file template
     *   although this possibility is explicitly permitted in the specs.
     * 4xx-5xx require a local file template.
     * - sending Location: on these codes with no body is invalid by the specs.
     * - current result is Squid crashing or XSS problems as dynamic deny_info load random disk files.
     * - a future redesign of the file loading may result in loading remote objects sent inline as local body.
     */
    if (info->page_redirect == HTTP_STATUS_NONE)
        ; // special case okay.
    else if (info->page_redirect < 200 || info->page_redirect > 599) {
        // out of range
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " is not valid on '" << page_name << "'");
        self_destruct();
    } else if ( /* >= 200 && */ info->page_redirect < 300 && strchr(&(page_name[4]), ':')) {
        // 2xx require a local template file
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a template on '" << page_name << "'");
        self_destruct();
    } else if (info->page_redirect >= 300 && info->page_redirect <= 399 && !strchr(&(page_name[4]), ':')) {
        // 3xx require an absolute URL
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a URL on '" << page_name << "'");
        self_destruct();
    } else if (info->page_redirect >= 400 /* && <= 599 */ && strchr(&(page_name[4]), ':')) {
        // 4xx/5xx require a local template file
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a template on '" << page_name << "'");
        self_destruct();
    }
    // else okay.

    return info;
}