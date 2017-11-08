static void ap_slotmem_plain_register_hook(apr_pool_t *p)
{
    /* XXX: static const char * const prePos[] = { "mod_slotmem.c", NULL }; */
    ap_register_provider(p, AP_SLOTMEM_PROVIDER_GROUP, "plain",
                         AP_SLOTMEM_PROVIDER_VERSION, &storage);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}