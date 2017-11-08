static const char *reflector_header(cmd_parms * cmd, void *dummy, const char *in,
        const char *out)
{
    reflector_cfg *cfg = (reflector_cfg *) dummy;

    apr_table_addn(cfg->headers, in, out ? out : in);

    return NULL;
}