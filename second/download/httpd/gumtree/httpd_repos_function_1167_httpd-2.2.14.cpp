static const char *cmd_rewritelock(cmd_parms *cmd, void *dconf, const char *a1)
{
    const char *error;

    if ((error = ap_check_cmd_context(cmd, GLOBAL_ONLY)) != NULL)
        return error;

    /* fixup the path, especially for rewritelock_remove() */
    lockname = ap_server_root_relative(cmd->pool, a1);

    if (!lockname) {
        return apr_pstrcat(cmd->pool, "Invalid RewriteLock path ", a1);
    }

    return NULL;
}