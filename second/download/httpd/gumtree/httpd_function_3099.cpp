static int check_dir_access(request_rec *r)
{
    int method = r->method_number;
    int ret = OK;
    access_compat_dir_conf *a = (access_compat_dir_conf *)
        ap_get_module_config(r->per_dir_config, &access_compat_module);

    if (a->order[method] == ALLOW_THEN_DENY) {
        ret = HTTP_FORBIDDEN;
        if (find_allowdeny(r, a->allows, method)) {
            ret = OK;
        }
        if (find_allowdeny(r, a->denys, method)) {
            ret = HTTP_FORBIDDEN;
        }
    }
    else if (a->order[method] == DENY_THEN_ALLOW) {
        if (find_allowdeny(r, a->denys, method)) {
            ret = HTTP_FORBIDDEN;
        }
        if (find_allowdeny(r, a->allows, method)) {
            ret = OK;
        }
    }
    else {
        if (find_allowdeny(r, a->allows, method)
            && !find_allowdeny(r, a->denys, method)) {
            ret = OK;
        }
        else {
            ret = HTTP_FORBIDDEN;
        }
    }

    if (ret == HTTP_FORBIDDEN) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "client denied by server configuration: %s%s",
                      r->filename ? "" : "uri ",
                      r->filename ? r->filename : r->uri);
    }

    return ret;
}