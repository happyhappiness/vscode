static char *
menu_url(cachemgr_request * req, const char *action)
{
    static char url[1024];
    snprintf(url, sizeof(url), "%s?host=%s&port=%d&user_name=%s&operation=%s&auth=%s",
             script_name,
             req->hostname,
             req->port,
             safe_str(req->user_name),
             action,
             safe_str(req->pub_auth));
    return url;
}