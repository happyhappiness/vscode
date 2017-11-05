static const char *load_file(cmd_parms *cmd, void *dummy, const char *filename)
{
    apr_dso_handle_t *handle;
    const char *file;

    file = ap_server_root_relative(cmd->pool, filename);

    if (!file) {
        return apr_pstrcat(cmd->pool, "Invalid LoadFile path ",
                           filename, NULL);
    }

    if (apr_dso_load(&handle, file, cmd->pool) != APR_SUCCESS) {
        char my_error[256];

        return apr_pstrcat(cmd->pool, "Cannot load ", filename,
                          " into server: ",
                          apr_dso_error(handle, my_error, sizeof(my_error)),
                          NULL);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(01576)
                 "loaded file %s", filename);

    return NULL;
}