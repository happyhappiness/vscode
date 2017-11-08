static char *lookup_variable(request_rec *r, char *var)
{
    const char *result;
    char resultbuf[LONG_STRING_LEN];
    apr_time_exp_t tm;
    request_rec *rsub;

    result = NULL;

    /* HTTP headers */
    if (strcasecmp(var, "HTTP_USER_AGENT") == 0) {
        result = lookup_header(r, "User-Agent");
    }
    else if (strcasecmp(var, "HTTP_REFERER") == 0) {
        result = lookup_header(r, "Referer");
    }
    else if (strcasecmp(var, "HTTP_COOKIE") == 0) {
        result = lookup_header(r, "Cookie");
    }
    else if (strcasecmp(var, "HTTP_FORWARDED") == 0) {
        result = lookup_header(r, "Forwarded");
    }
    else if (strcasecmp(var, "HTTP_HOST") == 0) {
        result = lookup_header(r, "Host");
    }
    else if (strcasecmp(var, "HTTP_PROXY_CONNECTION") == 0) {
        result = lookup_header(r, "Proxy-Connection");
    }
    else if (strcasecmp(var, "HTTP_ACCEPT") == 0) {
        result = lookup_header(r, "Accept");
    }
    /* all other headers from which we are still not know about */
    else if (strlen(var) > 5 && strncasecmp(var, "HTTP:", 5) == 0) {
        result = lookup_header(r, var+5);
    }

    /* connection stuff */
    else if (strcasecmp(var, "REMOTE_ADDR") == 0) {
        result = r->connection->remote_ip;
    }
    else if (strcasecmp(var, "REMOTE_PORT") == 0) {
        return apr_itoa(r->pool, r->connection->remote_addr->port);
    }
    else if (strcasecmp(var, "REMOTE_HOST") == 0) {
        result = (char *)ap_get_remote_host(r->connection,
                                            r->per_dir_config, REMOTE_NAME, NULL);
    }
    else if (strcasecmp(var, "REMOTE_USER") == 0) {
        result = r->user;
    }
    else if (strcasecmp(var, "REMOTE_IDENT") == 0) {
        result = (char *)ap_get_remote_logname(r);
    }

    /* request stuff */
    else if (strcasecmp(var, "THE_REQUEST") == 0) { /* non-standard */
        result = r->the_request;
    }
    else if (strcasecmp(var, "REQUEST_METHOD") == 0) {
        result = r->method;
    }
    else if (strcasecmp(var, "REQUEST_URI") == 0) { /* non-standard */
        result = r->uri;
    }
    else if (strcasecmp(var, "SCRIPT_FILENAME") == 0 ||
             strcasecmp(var, "REQUEST_FILENAME") == 0  ) {
        result = r->filename;
    }
    else if (strcasecmp(var, "PATH_INFO") == 0) {
        result = r->path_info;
    }
    else if (strcasecmp(var, "QUERY_STRING") == 0) {
        result = r->args;
    }
    else if (strcasecmp(var, "AUTH_TYPE") == 0) {
        result = r->ap_auth_type;
    }
    else if (strcasecmp(var, "IS_SUBREQ") == 0) { /* non-standard */
        result = (r->main != NULL ? "true" : "false");
    }

    /* internal server stuff */
    else if (strcasecmp(var, "DOCUMENT_ROOT") == 0) {
        result = ap_document_root(r);
    }
    else if (strcasecmp(var, "SERVER_ADMIN") == 0) {
        result = r->server->server_admin;
    }
    else if (strcasecmp(var, "SERVER_NAME") == 0) {
        result = ap_get_server_name(r);
    }
    else if (strcasecmp(var, "SERVER_ADDR") == 0) { /* non-standard */
        result = r->connection->local_ip;
    }
    else if (strcasecmp(var, "SERVER_PORT") == 0) {
        apr_snprintf(resultbuf, sizeof(resultbuf), "%u", ap_get_server_port(r));
        result = resultbuf;
    }
    else if (strcasecmp(var, "SERVER_PROTOCOL") == 0) {
        result = r->protocol;
    }
    else if (strcasecmp(var, "SERVER_SOFTWARE") == 0) {
        result = ap_get_server_version();
    }
    else if (strcasecmp(var, "API_VERSION") == 0) { /* non-standard */
        apr_snprintf(resultbuf, sizeof(resultbuf), "%d:%d",
                     MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
        result = resultbuf;
    }

/* XXX: wow this has gotta be slow if you actually use it for a lot, recalculates exploded time for each variable */
    /* underlaying Unix system stuff */
    else if (strcasecmp(var, "TIME_YEAR") == 0) {
        apr_time_exp_lt(&tm, apr_time_now());
        apr_snprintf(resultbuf, sizeof(resultbuf), "%04d", tm.tm_year + 1900);
        result = resultbuf;
    }
#define MKTIMESTR(format, tmfield) \
    apr_time_exp_lt(&tm, apr_time_now()); \
    apr_snprintf(resultbuf, sizeof(resultbuf), format, tm.tmfield); \
    result = resultbuf;
    else if (strcasecmp(var, "TIME_MON") == 0) {
        MKTIMESTR("%02d", tm_mon+1)
    }
    else if (strcasecmp(var, "TIME_DAY") == 0) {
        MKTIMESTR("%02d", tm_mday)
    }
    else if (strcasecmp(var, "TIME_HOUR") == 0) {
        MKTIMESTR("%02d", tm_hour)
    }
    else if (strcasecmp(var, "TIME_MIN") == 0) {
        MKTIMESTR("%02d", tm_min)
    }
    else if (strcasecmp(var, "TIME_SEC") == 0) {
        MKTIMESTR("%02d", tm_sec)
    }
    else if (strcasecmp(var, "TIME_WDAY") == 0) {
        MKTIMESTR("%d", tm_wday)
    }
    else if (strcasecmp(var, "TIME") == 0) {
        apr_time_exp_lt(&tm, apr_time_now());
        apr_snprintf(resultbuf, sizeof(resultbuf),
                     "%04d%02d%02d%02d%02d%02d", tm.tm_year + 1900,
                     tm.tm_mon+1, tm.tm_mday,
                     tm.tm_hour, tm.tm_min, tm.tm_sec);
        result = resultbuf;
        rewritelog(r, 1, "RESULT='%s'", result);
    }

    /* all other env-variables from the parent Apache process */
    else if (strlen(var) > 4 && strncasecmp(var, "ENV:", 4) == 0) {
        /* first try the internal Apache notes structure */
        result = apr_table_get(r->notes, var+4);
        /* second try the internal Apache env structure  */
        if (result == NULL) {
            result = apr_table_get(r->subprocess_env, var+4);
        }
        /* third try the external OS env */
        if (result == NULL) {
            result = getenv(var+4);
        }
    }
    else if (strlen(var) > 4 && !strncasecmp(var, "SSL:", 4) 
             && rewrite_ssl_lookup) {
        result = rewrite_ssl_lookup(r->pool, r->server, r->connection, r, 
                                    var + 4);
    }

#define LOOKAHEAD(subrecfunc) \
        if ( \
          /* filename is safe to use */ \
          r->filename != NULL \
              /* - and we're either not in a subrequest */ \
              && ( r->main == NULL \
                  /* - or in a subrequest where paths are non-NULL... */ \
                    || ( r->main->uri != NULL && r->uri != NULL \
                        /*   ...and sub and main paths differ */ \
                        && strcmp(r->main->uri, r->uri) != 0))) { \
            /* process a file-based subrequest */ \
            rsub = subrecfunc(r->filename, r, NULL); \
            /* now recursively lookup the variable in the sub_req */ \
            result = lookup_variable(rsub, var+5); \
            /* copy it up to our scope before we destroy sub_req's apr_pool_t */ \
            result = apr_pstrdup(r->pool, result); \
            /* cleanup by destroying the subrequest */ \
            ap_destroy_sub_req(rsub); \
            /* log it */ \
            rewritelog(r, 5, "lookahead: path=%s var=%s -> val=%s", \
                       r->filename, var+5, result); \
            /* return ourself to prevent re-pstrdup */ \
            return (char *)result; \
        }

    /* look-ahead for parameter through URI-based sub-request */
    else if (strlen(var) > 5 && strncasecmp(var, "LA-U:", 5) == 0) {
        LOOKAHEAD(ap_sub_req_lookup_uri)
    }
    /* look-ahead for parameter through file-based sub-request */
    else if (strlen(var) > 5 && strncasecmp(var, "LA-F:", 5) == 0) {
        LOOKAHEAD(ap_sub_req_lookup_file)
    }

    /* file stuff */
    else if (strcasecmp(var, "SCRIPT_USER") == 0) {
        result = "<unknown>";
        if (r->finfo.valid & APR_FINFO_USER) {
            apr_get_username((char **)&result, r->finfo.user, r->pool);
        }
    }
    else if (strcasecmp(var, "SCRIPT_GROUP") == 0) {
        result = "<unknown>";
        if (r->finfo.valid & APR_FINFO_GROUP) {
            apr_group_name_get((char **)&result, r->finfo.group, r->pool);
        }
    } else if (strcasecmp(var, "HTTPS") == 0) {
        int flag = rewrite_is_https && rewrite_is_https(r->connection);
        result = flag ? "on" : "off";
    }

    if (result == NULL) {
        return apr_pstrdup(r->pool, "");
    }
    else {
        return apr_pstrdup(r->pool, result);
    }
}