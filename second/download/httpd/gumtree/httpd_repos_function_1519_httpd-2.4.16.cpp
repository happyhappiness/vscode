static void register_hooks(apr_pool_t *p)
{
    static const char * const aszPre[]={ "mod_alias.c","mod_userdir.c",NULL };

    ap_hook_translate_name(mva_translate, aszPre, NULL, APR_HOOK_MIDDLE);
}