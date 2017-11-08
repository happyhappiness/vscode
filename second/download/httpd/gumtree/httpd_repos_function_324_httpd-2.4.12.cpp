static dav_error * dav_process_if_header(request_rec *r, dav_if_header **p_ih)
{
    dav_error *err;
    char *str;
    char *list;
    const char *state_token;
    const char *uri = NULL;        /* scope of current production; NULL=no-tag */
    apr_size_t uri_len = 0;
    apr_status_t rv;
    dav_if_header *ih = NULL;
    apr_uri_t parsed_uri;
    const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    enum {no_tagged, tagged, unknown} list_type = unknown;
    int condition;

    *p_ih = NULL;

    if ((str = apr_pstrdup(r->pool, apr_table_get(r->headers_in, "If"))) == NULL)
        return NULL;

    while (*str) {
        switch(*str) {
        case '<':
            /* Tagged-list production - following states apply to this uri */
            if (list_type == no_tagged
                || ((uri = dav_fetch_next_token(&str, '>')) == NULL)) {
                return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                     DAV_ERR_IF_TAGGED, 0,
                                     "Invalid If-header: unclosed \"<\" or "
                                     "unexpected tagged-list production.");
            }

            /* 2518 specifies this must be an absolute URI; just take the
             * relative part for later comparison against r->uri */
            if ((rv = apr_uri_parse(r->pool, uri, &parsed_uri)) != APR_SUCCESS
                || !parsed_uri.path) {
                return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                     DAV_ERR_IF_TAGGED, rv,
                                     "Invalid URI in tagged If-header.");
            }
            /* note that parsed_uri.path is allocated; we can trash it */

            /* clean up the URI a bit */
            ap_getparents(parsed_uri.path);

            /* the resources we will compare to have unencoded paths */
            if (ap_unescape_url(parsed_uri.path) != OK) {
                return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                     DAV_ERR_IF_TAGGED, rv,
                                     "Invalid percent encoded URI in "
                                     "tagged If-header.");
            }

            uri_len = strlen(parsed_uri.path);
            if (uri_len > 1 && parsed_uri.path[uri_len - 1] == '/') {
                parsed_uri.path[--uri_len] = '\0';
            }

            uri = parsed_uri.path;
            list_type = tagged;
            break;

        case '(':
            /* List production */

            /* If a uri has not been encountered, this is a No-Tagged-List */
            if (list_type == unknown)
                list_type = no_tagged;

            if ((list = dav_fetch_next_token(&str, ')')) == NULL) {
                return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                     DAV_ERR_IF_UNCLOSED_PAREN, 0,
                                     "Invalid If-header: unclosed \"(\".");
            }

            if ((ih = dav_add_if_resource(r->pool, ih, uri, uri_len)) == NULL) {
                /* ### dav_add_if_resource() should return an error for us! */
                return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                     DAV_ERR_IF_PARSE, 0,
                                     "Internal server error parsing \"If:\" "
                                     "header.");
            }

            condition = DAV_IF_COND_NORMAL;

            while (*list) {
                /* List is the entire production (in a uri scope) */

                switch (*list) {
                case '<':
                    if ((state_token = dav_fetch_next_token(&list, '>')) == NULL) {
                        /* ### add a description to this error */
                        return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                             DAV_ERR_IF_PARSE, 0, NULL);
                    }

                    if ((err = dav_add_if_state(r->pool, ih, state_token, dav_if_opaquelock,
                                                condition, locks_hooks)) != NULL) {
                        /* ### maybe add a higher level description */
                        return err;
                    }
                    condition = DAV_IF_COND_NORMAL;
                    break;

                case '[':
                    if ((state_token = dav_fetch_next_token(&list, ']')) == NULL) {
                        /* ### add a description to this error */
                        return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                             DAV_ERR_IF_PARSE, 0, NULL);
                    }

                    if ((err = dav_add_if_state(r->pool, ih, state_token, dav_if_etag,
                                                condition, locks_hooks)) != NULL) {
                        /* ### maybe add a higher level description */
                        return err;
                    }
                    condition = DAV_IF_COND_NORMAL;
                    break;

                case 'N':
                    if (list[1] == 'o' && list[2] == 't') {
                        if (condition != DAV_IF_COND_NORMAL) {
                            return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                                 DAV_ERR_IF_MULTIPLE_NOT, 0,
                                                 "Invalid \"If:\" header: "
                                                 "Multiple \"not\" entries "
                                                 "for the same state.");
                        }
                        condition = DAV_IF_COND_NOT;
                    }
                    list += 2;
                    break;

                case ' ':
                case '\t':
                    break;

                default:
                    return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                         DAV_ERR_IF_UNK_CHAR, 0,
                                         apr_psprintf(r->pool,
                                                     "Invalid \"If:\" "
                                                     "header: Unexpected "
                                                     "character encountered "
                                                     "(0x%02x, '%c').",
                                                     *list, *list));
                }

                list++;
            }
            break;

        case ' ':
        case '\t':
            break;

        default:
            return dav_new_error(r->pool, HTTP_BAD_REQUEST,
                                 DAV_ERR_IF_UNK_CHAR, 0,
                                 apr_psprintf(r->pool,
                                             "Invalid \"If:\" header: "
                                             "Unexpected character "
                                             "encountered (0x%02x, '%c').",
                                             *str, *str));
        }

        str++;
    }

    *p_ih = ih;
    return NULL;
}