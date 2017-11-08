static void register_hooks(apr_pool_t *p)
{
    static const char * const aszPre[]={ "mod_mime.c", NULL };

    /* mod_mime_magic should be run after mod_mime, if at all. */

    ap_hook_type_checker(magic_find_ct, aszPre, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(magic_init, NULL, NULL, APR_HOOK_FIRST);
}