
AP_DECLARE(void) ap_register_hooks(module *m, apr_pool_t *p)
{
    if (m->register_hooks) {
        if (getenv("SHOW_HOOKS")) {
            printf("Registering hooks for %s\n", m->name);
            apr_debug_module_hooks = 1;
        }

        apr_current_hooking_module = m->name;
        m->register_hooks(p);
    }
}

/* One-time setup for precompiled modules --- NOT to be done on restart */

