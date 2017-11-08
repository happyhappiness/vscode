static int core_override_type(request_rec *r)
{
    core_dir_config *conf =
        (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                &core_module);

    /* Check for overrides with ForceType / SetHandler
     */
    if (conf->mime_type && strcmp(conf->mime_type, "none"))
        ap_set_content_type(r, (char*) conf->mime_type);

    if (conf->handler && strcmp(conf->handler, "none"))
        r->handler = conf->handler;

    /* Deal with the poor soul who is trying to force path_info to be
     * accepted within the core_handler, where they will let the subreq
     * address its contents.  This is toggled by the user in the very
     * beginning of the fixup phase (here!), so modules should override the user's
     * discretion in their own module fixup phase.  It is tristate, if
     * the user doesn't specify, the result is AP_REQ_DEFAULT_PATH_INFO.
     * (which the module may interpret to its own customary behavior.)  
     * It won't be touched if the value is no longer AP_ACCEPT_PATHINFO_UNSET,
     * so any module changing the value prior to the fixup phase 
     * OVERRIDES the user's choice.
     */
    if ((r->used_path_info == AP_REQ_DEFAULT_PATH_INFO)
        && (conf->accept_path_info != AP_ACCEPT_PATHINFO_UNSET)) {
        /* No module knew better, and the user coded AcceptPathInfo */
        r->used_path_info = conf->accept_path_info;
    }

    return OK;
}