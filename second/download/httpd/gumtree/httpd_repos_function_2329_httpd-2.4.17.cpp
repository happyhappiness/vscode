void h2_switch_register_hooks(void)
{
    ap_hook_protocol_propose(h2_protocol_propose, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_protocol_switch(h2_protocol_switch, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_protocol_get(h2_protocol_get, NULL, NULL, APR_HOOK_MIDDLE);
}