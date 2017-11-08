static void register_hooks(apr_pool_t *p)
{
    static const char * const aszPre[]={ "mod_alias.c",NULL };
    static const char * const aszSucc[]={ "mod_vhost_alias.c",NULL };

    ap_hook_translate_name(translate_userdir,aszPre,aszSucc,APR_HOOK_MIDDLE);
#ifdef HAVE_UNIX_SUEXEC
    ap_hook_get_suexec_identity(get_suexec_id_doer,NULL,NULL,APR_HOOK_FIRST);
#endif
}