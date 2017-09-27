     * doubled slashes)
     */

    return urip - uri;
}

static char *try_alias_list(request_rec *r, apr_array_header_t *aliases,
                            int doesc, int *status)
{
    alias_entry *entries = (alias_entry *) aliases->elts;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    char *found = NULL;
    int i;

    for (i = 0; i < aliases->nelts; ++i) {
        alias_entry *p = &entries[i];
        int l;

        if (p->regexp) {
            if (!ap_regexec(p->regexp, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
                if (p->real) {
                    found = ap_pregsub(r->pool, p->real, r->uri,
                                       AP_MAX_REG_MATCH, regm);
                    if (found && doesc) {
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
                }
                else {
                    /* need something non-null */
                    found = apr_pstrdup(r->pool, "");
                }
            }
        }
        else {
            l = alias_matches(r->uri, p->fake);

            if (l > 0) {
                if (doesc) {
                    char *escurl;
                    escurl = ap_os_escape_path(r->pool, r->uri + l, 1);

                    found = apr_pstrcat(r->pool, p->real, escurl, NULL);
                }
                else
                    found = apr_pstrcat(r->pool, p->real, r->uri + l, NULL);
            }
        }

        if (found) {
            if (p->handler) {    /* Set handler, and leave a note for mod_cgi */
                r->handler = p->handler;
                apr_table_setn(r->notes, "alias-forced-type", r->handler);
            }
            /* XXX This is as SLOW as can be, next step, we optimize
             * and merge to whatever part of the found path was already
             * canonicalized.  After I finish eliminating os canonical.
             * Better fail test for ap_server_root_relative needed here.
             */
            if (!doesc) {
                found = ap_server_root_relative(r->pool, found);
            }
            if (found) {
                *status = p->redir_status;
            }
            return found;
        }

    }

