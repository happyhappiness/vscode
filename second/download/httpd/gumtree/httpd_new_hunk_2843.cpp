     * doubled slashes)
     */

    return urip - uri;
}

static char magic_error_value;
#define PREGSUB_ERROR      (&magic_error_value)

static char *try_alias_list(request_rec *r, apr_array_header_t *aliases,
                            int is_redir, int *status)
{
    alias_entry *entries = (alias_entry *) aliases->elts;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    char *found = NULL;
    int i;

    for (i = 0; i < aliases->nelts; ++i) {
        alias_entry *alias = &entries[i];
        int l;

        if (alias->regexp) {
            if (!ap_regexec(alias->regexp, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
                if (alias->real) {
                    found = ap_pregsub(r->pool, alias->real, r->uri,
                                       AP_MAX_REG_MATCH, regm);
                    if (found) {
                       if (is_redir) {
                            apr_uri_t uri;
                            apr_uri_parse(r->pool, found, &uri);
                            /* Do not escape the query string or fragment. */
                            found = apr_uri_unparse(r->pool, &uri,
                                                    APR_URI_UNP_OMITQUERY);
                            found = ap_escape_uri(r->pool, found);
                            if (uri.query) {
                                found = apr_pstrcat(r->pool, found, "?",
                                                    uri.query, NULL);
                            }
                            if (uri.fragment) {
                                found = apr_pstrcat(r->pool, found, "#",
                                                    uri.fragment, NULL);
                            }
                       }
                       else {
                           int pathlen = strlen(found) -
                                         (strlen(r->uri + regm[0].rm_eo));
                           AP_DEBUG_ASSERT(pathlen >= 0);
                           AP_DEBUG_ASSERT(pathlen <= strlen(found));
                           ap_set_context_info(r,
                                               apr_pstrmemdup(r->pool, r->uri,
                                                              regm[0].rm_eo),
                                               apr_pstrmemdup(r->pool, found,
                                                              pathlen));
                       }
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00672)
                                      "Regex substitution in '%s' failed. "
                                      "Replacement too long?", alias->real);
                        return PREGSUB_ERROR;
                    }
                }
                else {
                    /* need something non-null */
                    found = "";
                }
            }
        }
        else {
            l = alias_matches(r->uri, alias->fake);

            if (l > 0) {
                ap_set_context_info(r, alias->fake, alias->real);
                if (is_redir) {
                    char *escurl;
                    escurl = ap_os_escape_path(r->pool, r->uri + l, 1);

                    found = apr_pstrcat(r->pool, alias->real, escurl, NULL);
                }
                else
                    found = apr_pstrcat(r->pool, alias->real, r->uri + l, NULL);
            }
        }

        if (found) {
            if (alias->handler) {    /* Set handler, and leave a note for mod_cgi */
                r->handler = alias->handler;
                apr_table_setn(r->notes, "alias-forced-type", r->handler);
            }
            /* XXX This is as SLOW as can be, next step, we optimize
             * and merge to whatever part of the found path was already
             * canonicalized.  After I finish eliminating os canonical.
             * Better fail test for ap_server_root_relative needed here.
             */
            if (!is_redir) {
                found = ap_server_root_relative(r->pool, found);
            }
            if (found) {
                *status = alias->redir_status;
            }
            return found;
        }

    }

