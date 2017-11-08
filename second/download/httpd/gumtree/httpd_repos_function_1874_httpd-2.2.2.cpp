static const char *set_nonce_format(cmd_parms *cmd, void *config,
                                    const char *fmt)
{
    ((digest_config_rec *) config)->nonce_format = fmt;
    return "AuthDigestNonceFormat is not implemented (yet)";
}