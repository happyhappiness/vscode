static int modssl_is_prelinked(void)
{
    apr_size_t i = 0;
    const module *mod;
    while ((mod = ap_prelinked_modules[i++])) {
        if (strcmp(mod->name, "mod_ssl.c") == 0) {
            return 1;
        }
    }
    return 0;
}