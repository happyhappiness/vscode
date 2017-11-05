int ssl_dh_InitParams(server_rec *s)
{
    unsigned n;

    for (n = 0; n < sizeof(dhparams)/sizeof(dhparams[0]); n++) {
        const unsigned int bits =
            dhparams[n].min ? (dhparams[n].min - 1) * 2 : 512;
#ifdef HAVE_FIPS
        if (bits < 1024 && FIPS_mode()) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "Init: Skipping generating temporary "
                         "%u bit DH parameters in FIPS mode", bits);
            continue;
        }
#endif
        dhparams[n].dh = dhparams[n].make();
        if (!dhparams[n].dh) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "Init: Failed to generate temporary "
                         "%u bit DH parameters", bits);
            return !OK;
        }
    }
    return OK;
}