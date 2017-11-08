static int isSecureConnUpgradeable (const server_rec *s, const conn_rec *c)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(s);

    return isSecureConnEx (s, c, sc->slutable);
}