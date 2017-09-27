 * shared object file into the adress space of the server process.
 */

static const char *load_file(cmd_parms *cmd, void *dummy, const char *filename)
{
    apr_dso_handle_t *handle;
    const char *used_file, *error;

    error = dso_load(cmd, &handle, filename, &used_file);
    if (error)
        return error;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(01576)
                 "loaded file %s", used_file);

    return NULL;
}

static module *ap_find_loaded_module_symbol(server_rec *s, const char *modname)
{
