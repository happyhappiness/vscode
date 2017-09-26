
        apr_hook_debug_current = m->name;
        m->register_hooks(p);
    }
}

/* One-time setup for precompiled modules --- NOT to be done on restart */

AP_DECLARE(void) ap_add_module(module *m, apr_pool_t *p)
{
    /* This could be called from an AddModule httpd.conf command,
     * after the file has been linked and the module structure within it
     * teased out...
     */

    if (m->version != MODULE_MAGIC_NUMBER_MAJOR) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: module \"%s\" is not compatible with this "
                     "version of Apache (found %d, need %d).",
                     ap_server_argv0, m->name, m->version,
                     MODULE_MAGIC_NUMBER_MAJOR);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Please contact the vendor for the correct version.");
        exit(1);
    }

    if (m->next == NULL) {
        m->next = ap_top_module;
        ap_top_module = m;
    }

    if (m->module_index == -1) {
        m->module_index = total_modules++;
        dynamic_modules++;

        if (dynamic_modules > DYNAMIC_MODULE_LIMIT) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "%s: module \"%s\" could not be loaded, because"
                         " the dynamic", ap_server_argv0, m->name);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "module limit was reached. Please increase "
                         "DYNAMIC_MODULE_LIMIT and recompile.");
            exit(1);
        }
    }

    /* Some C compilers put a complete path into __FILE__, but we want
     * only the filename (e.g. mod_includes.c). So check for path
     * components (Unix and DOS), and remove them.
