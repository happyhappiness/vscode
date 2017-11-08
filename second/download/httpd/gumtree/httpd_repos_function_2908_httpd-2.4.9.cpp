static const char *authz_dbd_prepare(cmd_parms *cmd, void *cfg,
                                     const char *query)
{
    static unsigned int label_num = 0;
    char *label;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;

    if (dbd_prepare == NULL) {
        dbd_prepare = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_prepare);
        if (dbd_prepare == NULL) {
            return "You must load mod_dbd to enable AuthzDBD functions";
        }
        dbd_handle = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_acquire);
    }
    label = apr_psprintf(cmd->pool, "authz_dbd_%d", ++label_num);

    dbd_prepare(cmd->server, query, label);

    /* save the label here for our own use */
    return ap_set_string_slot(cmd, cfg, label);
}