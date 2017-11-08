static void check_modules(void) 
{
    int i;
    if (!checked) {
        for (i = 0; ap_loaded_modules[i]; ++i) {
            module *m = ap_loaded_modules[i];
            if (!strcmp("event.c", m->name)) {
                mpm_type = H2_MPM_EVENT;
                mpm_module = m;
            }
            else if (!strcmp("worker.c", m->name)) {
                mpm_type = H2_MPM_WORKER;
                mpm_module = m;
            }
            else if (!strcmp("prefork.c", m->name)) {
                mpm_type = H2_MPM_PREFORK;
                mpm_module = m;
            }
            else if (!strcmp("mod_ssl.c", m->name)) {
                ssl_module = m;
            }
        }
        checked = 1;
    }
}