static const char *request_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    int index = ((const char **)data - request_var_names);
    request_rec *r = ctx->r;
    if (!r)
        return "";

    switch (index) {
    case 0:
        return r->method;
    case 1:
        return ap_http_scheme(r);
    case 2:
        return r->uri;
    case 3:
        return r->filename;
    case 4:
        return ap_get_remote_host(r->connection, r->per_dir_config,
                                  REMOTE_NAME, NULL);
    case 5:
        return ap_get_remote_logname(r);
    case 6:
        return r->user;
    case 7:
        return r->server->server_admin;
    case 8:
        return ap_get_server_name_for_url(r);
    case 9:
        return apr_psprintf(ctx->p, "%u", ap_get_server_port(r));
    case 10:
        return r->protocol;
    case 11:
        return r->filename;
    case 12:
        return r->path_info;
    case 13:
        return r->args;
    case 14:
        return (r->main != NULL ? "true" : "false");
    case 15:
        return ap_document_root(r);
    case 16:
        return r->ap_auth_type;
    case 17:
        return r->the_request;
    case 18:
        return r->content_type;
    case 19:
        return r->handler;
    case 20:
        return r->log_id;
    case 21:
        {
            char *result = "";
            if (r->finfo.valid & APR_FINFO_USER)
                apr_uid_name_get(&result, r->finfo.user, ctx->p);
            return result;
        }
    case 22:
        {
            char *result = "";
            if (r->finfo.valid & APR_FINFO_USER)
                apr_gid_name_get(&result, r->finfo.group, ctx->p);
            return result;
        }
    case 23:
        return r->uri;
    case 24:
        {
            apr_time_exp_t tm;
            apr_time_exp_lt(&tm, r->mtime);
            return apr_psprintf(ctx->p, "%02d%02d%02d%02d%02d%02d%02d",
                                (tm.tm_year / 100) + 19, (tm.tm_year % 100),
                                tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min,
                                tm.tm_sec);
        }
    case 25:
        return ap_context_prefix(r);
    case 26:
        return ap_context_document_root(r);
    case 27:
        return r->status ? apr_psprintf(ctx->p, "%d", r->status) : "";
    case 28:
        return r->useragent_ip;
    default:
        ap_assert(0);
        return NULL;
    }
}