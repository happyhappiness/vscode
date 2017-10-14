static int read_type_map(apr_file_t **map, negotiation_state *neg,
                         request_rec *rr)
{
    request_rec *r = neg->r;
    apr_file_t *map_ = NULL;
    apr_status_t status;
    char buffer[MAX_STRING_LEN];
    enum header_state hstate;
    struct var_rec mime_info;
    int has_content;

    if (!map)
        map = &map_;

    /* We are not using multiviews */
    neg->count_multiviews_variants = 0;

    if ((status = apr_file_open(map, rr->filename, APR_READ | APR_BUFFERED,
                APR_OS_DEFAULT, neg->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "cannot access type map file: %s", rr->filename);
        if (APR_STATUS_IS_ENOTDIR(status) || APR_STATUS_IS_ENOENT(status)) {
            return HTTP_NOT_FOUND;
        }
        else {
            return HTTP_FORBIDDEN;
        }
    }

    clean_var_rec(&mime_info);
    has_content = 0;

    do {
        hstate = get_header_line(buffer, MAX_STRING_LEN, *map);

        if (hstate == header_seen) {
            char *body1 = lcase_header_name_return_body(buffer, neg->r);
            const char *body;

            if (body1 == NULL) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            strip_paren_comments(body1);
            body = body1;

            if (!strncmp(buffer, "uri:", 4)) {
                mime_info.file_name = ap_get_token(neg->pool, &body, 0);
            }
            else if (!strncmp(buffer, "content-type:", 13)) {
                struct accept_rec accept_info;

                get_entry(neg->pool, &accept_info, body);
                set_mime_fields(&mime_info, &accept_info);
                has_content = 1;
            }
            else if (!strncmp(buffer, "content-length:", 15)) {
                char *errp;
                apr_off_t number;

                if (apr_strtoff(&number, body, &errp, 10)
                    || *errp || number < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Parse error in type map, Content-Length: "
                                  "'%s' in %s is invalid.",
                                  body, r->filename);
                    break;
                }
                mime_info.bytes = number;
                has_content = 1;
            }
            else if (!strncmp(buffer, "content-language:", 17)) {
                mime_info.content_languages = do_languages_line(neg->pool,
                                                                &body);
                has_content = 1;
            }
            else if (!strncmp(buffer, "content-encoding:", 17)) {
                mime_info.content_encoding = ap_get_token(neg->pool, &body, 0);
                has_content = 1;
            }
            else if (!strncmp(buffer, "description:", 12)) {
                char *desc = apr_pstrdup(neg->pool, body);
                char *cp;

                for (cp = desc; *cp; ++cp) {
                    if (*cp=='\n') *cp=' ';
                }
                if (cp>desc) *(cp-1)=0;
                mime_info.description = desc;
            }
            else if (!strncmp(buffer, "body:", 5)) {
                char *tag = apr_pstrdup(neg->pool, body);
                char *eol = strchr(tag, '\0');
                apr_size_t len = MAX_STRING_LEN;
                while (--eol >= tag && apr_isspace(*eol))
                    *eol = '\0';
                if ((mime_info.body = get_body(buffer, &len, tag, *map)) < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Syntax error in type map, no end tag '%s'"
                                  "found in %s for Body: content.",
                                  tag, r->filename);
                     break;
                }
                mime_info.bytes = len;
                mime_info.file_name = apr_filepath_name_get(rr->filename);
            }
        }
        else {
            if (*mime_info.file_name && has_content) {
                void *new_var = apr_array_push(neg->avail_vars);

                memcpy(new_var, (void *) &mime_info, sizeof(var_rec));
            }

            clean_var_rec(&mime_info);
            has_content = 0;
        }
    } while (hstate != header_eof);

    if (map_)
        apr_file_close(map_);

    set_vlist_validator(r, rr);

    return OK;
}