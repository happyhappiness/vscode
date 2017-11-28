static void dump_sslproxy_cert_sign(StoreEntry *entry, const char *name, sslproxy_cert_sign *cert_sign)
{
    sslproxy_cert_sign *cs;
    for (cs = cert_sign; cs != NULL; cs = cs->next) {
        storeAppendPrintf(entry, "%s ", name);
        storeAppendPrintf(entry, "%s ", Ssl::certSignAlgorithm(cs->alg));
        if (cs->aclList)
            dump_acl_list(entry, cs->aclList);
        storeAppendPrintf(entry, "\n");
    }
}