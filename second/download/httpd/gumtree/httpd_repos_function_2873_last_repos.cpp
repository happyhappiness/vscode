void h2_alt_svc_register_hooks(void)
{
    ap_hook_post_read_request(h2_alt_svc_handler, NULL, NULL, APR_HOOK_MIDDLE);
}