static const char *set_balancer_nonce (cmd_parms *cmd, void *dummy, const char *arg,
                                       const char *val)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (!strcasecmp(arg, "None")) {
        *balancer_nonce = '\0';
    } else if (!strcasecmp(arg, "Set")) {
        if (val) {
            apr_cpystrn(balancer_nonce, val, sizeof(balancer_nonce));
        } else {
            return "BalancerNonce Set requires an argument";
        }
    } else if (strcasecmp(arg, "Default")) {
        return "Bad argument for BalancerNonce: Must be 'Set', 'None' or 'Default'";
    }
    return NULL;
}