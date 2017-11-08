static const char *dso_load(cmd_parms *cmd, apr_dso_handle_t **modhandlep,
                            const char *filename, const char **used_filename)
{
    int retry = 0;
    const char *fullname = ap_server_root_relative(cmd->temp_pool, filename);
    char my_error[256];
    if (filename != NULL && ap_strchr_c(filename, '/') == NULL) {
        /* retry on error without path to use dlopen()'s search path */
        retry = 1;
    }

    if (fullname == NULL && !retry) {
        return apr_psprintf(cmd->temp_pool, "Invalid %s path %s",
                            cmd->cmd->name, filename);
    }
    *used_filename = fullname;
    if (apr_dso_load(modhandlep, fullname, cmd->pool) == APR_SUCCESS) {
        return NULL;
    }
    if (retry) {
        *used_filename = filename;
        if (apr_dso_load(modhandlep, filename, cmd->pool) == APR_SUCCESS)
            return NULL;
    }

    return apr_pstrcat(cmd->temp_pool, "Cannot load ", filename,
                        " into server: ",
                        apr_dso_error(*modhandlep, my_error, sizeof(my_error)),
                        NULL);
}