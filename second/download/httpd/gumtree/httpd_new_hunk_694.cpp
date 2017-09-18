
AP_DECLARE(void) ap_register_hooks(module *m, apr_pool_t *p)
{
    if (m->register_hooks) {
        if (getenv("SHOW_HOOKS")) {
            printf("Registering hooks for %s\n", m->name);
            apr_hook_debug_enabled = 1;
        }

        apr_hook_debug_current = m->name;
        m->register_hooks(p);
    }
}

/* One-time setup for precompiled modules --- NOT to be done on restart */

