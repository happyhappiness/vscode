 *   SetHandler ldap-status
 * </Location>
 *
 */
static int util_ldap_handler(request_rec *r)
{
    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(r->server->module_config,
                                                 &ldap_module);

    r->allowed |= (1 << M_GET);
    if (r->method_number != M_GET)
        return DECLINED;

    if (strcmp(r->handler, "ldap-status")) {
        return DECLINED;
    }

    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

    if (r->header_only)
        return OK;

    ap_rputs(DOCTYPE_HTML_3_2
