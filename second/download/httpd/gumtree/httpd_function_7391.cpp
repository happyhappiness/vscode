static int ssl_tmp_key_init_dh(server_rec *s,
                               int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

#ifdef HAVE_FIPS

    if (FIPS_mode() && bits < 1024) {
        mc->pTmpKeys[idx] = NULL;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01880)
                     "Init: Skipping generating temporary "
                     "%d bit DH parameters in FIPS mode", bits);
        return OK;
    }

#endif

    if (!(mc->pTmpKeys[idx] =
          ssl_dh_GetTmpParam(bits)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01881)
                     "Init: Failed to generate temporary "
                     "%d bit DH parameters", bits);
        return !OK;
    }

    return OK;
}