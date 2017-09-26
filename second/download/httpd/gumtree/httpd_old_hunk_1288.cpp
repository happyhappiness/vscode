
static int ssl_tmp_key_init_rsa(server_rec *s,
                                int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          RSA_generate_key(bits, RSA_F4, NULL, NULL)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit RSA private key", bits);
        return !OK;
    }

    return OK;
}

static int ssl_tmp_key_init_dh(server_rec *s,
                               int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          ssl_dh_GetTmpParam(bits)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit DH parameters", bits);
