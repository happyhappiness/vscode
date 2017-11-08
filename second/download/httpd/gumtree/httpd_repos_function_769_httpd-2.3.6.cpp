const char *ssl_asn1_table_keyfmt(apr_pool_t *p,
                                  const char *id,
                                  int keytype)
{
    const char *keystr = ssl_asn1_keystr(keytype);

    return apr_pstrcat(p, id, ":", keystr, NULL);
}