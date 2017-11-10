static char* get_interpreter_from_win32_registry(apr_pool_t *p,
                                                 const char* ext,
                                                 int strict)
{
    apr_status_t rv;
    ap_regkey_t *name_key = NULL;
    ap_regkey_t *type_key;
    ap_regkey_t *key;
    char execcgi_path[] = "SHELL\\EXECCGI\\COMMAND";
    char execopen_path[] = "SHELL\\OPEN\\COMMAND";
    char *type_name;
    char *buffer;

    if (!ext) {
        return NULL;
    }
    /*
     * Future optimization:
     * When the registry is successfully searched, store the strings for
     * interpreter and arguments in an ext hash to speed up subsequent look-ups
     */

    /* Open the key associated with the script filetype extension */
    rv = ap_regkey_open(&type_key, AP_REGKEY_CLASSES_ROOT, ext, APR_READ, p);

    if (rv != APR_SUCCESS) {
        return NULL;
    }

    /* Retrieve the name of the script filetype extension */
    rv = ap_regkey_value_get(&type_name, type_key, "", p);

    if (rv == APR_SUCCESS && type_name[0]) {
        /* Open the key associated with the script filetype extension */
        rv = ap_regkey_open(&name_key, AP_REGKEY_CLASSES_ROOT, type_name,
                            APR_READ, p);
    }

    /* Open the key for the script command path by:
     *
     *   1) the 'named' filetype key for ExecCGI/Command
     *   2) the extension's type key for ExecCGI/Command
     *
     * and if the strict arg is false, then continue trying:
     *
     *   3) the 'named' filetype key for Open/Command
     *   4) the extension's type key for Open/Command
     */

    if (name_key) {
        if ((rv = ap_regkey_open(&key, name_key, execcgi_path, APR_READ, p))
                == APR_SUCCESS) {
            rv = ap_regkey_value_get(&buffer, key, "", p);
            ap_regkey_close(name_key);
        }
    }

    if (!name_key || (rv != APR_SUCCESS)) {
        if ((rv = ap_regkey_open(&key, type_key, execcgi_path, APR_READ, p))
                == APR_SUCCESS) {
            rv = ap_regkey_value_get(&buffer, key, "", p);
            ap_regkey_close(type_key);
        }
    }

    if (!strict && name_key && (rv != APR_SUCCESS)) {
        if ((rv = ap_regkey_open(&key, name_key, execopen_path, APR_READ, p))
                == APR_SUCCESS) {
            rv = ap_regkey_value_get(&buffer, key, "", p);
            ap_regkey_close(name_key);
        }
    }

    if (!strict && (rv != APR_SUCCESS)) {
        if ((rv = ap_regkey_open(&key, type_key, execopen_path, APR_READ, p))
                == APR_SUCCESS) {
            rv = ap_regkey_value_get(&buffer, key, "", p);
            ap_regkey_close(type_key);
        }
    }

    if (name_key) {
        ap_regkey_close(name_key);
    }

    ap_regkey_close(type_key);

    if (rv != APR_SUCCESS || !buffer[0]) {
        return NULL;
    }

    return buffer;
}