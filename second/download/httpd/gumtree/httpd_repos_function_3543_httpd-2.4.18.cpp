static int conf_vector_length_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                                         apr_pool_t *ptemp)
{
    /*
     * We have loaded all modules that are loaded by EXEC_ON_READ directives.
     * From now on we reduce the size of the config vectors to what we need,
     * plus what has been reserved (e.g. by mod_perl) for additional modules
     * loaded later on.
     * If max_modules is too small, ap_add_module() will abort.
     */
    if (total_modules + reserved_module_slots < max_modules) {
        conf_vector_length = total_modules + reserved_module_slots;
    }
    apr_pool_cleanup_register(pconf, NULL, reset_conf_vector_length,
                              apr_pool_cleanup_null);
    return OK;
}