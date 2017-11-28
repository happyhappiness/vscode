static void dump_sslproxy_cert_adapt(StoreEntry *entry, const char *name, sslproxy_cert_adapt *cert_adapt)
{
    for (sslproxy_cert_adapt *ca = cert_adapt; ca != NULL; ca = ca->next) {
        storeAppendPrintf(entry, "%s ", name);
        storeAppendPrintf(entry, "%s{%s} ", Ssl::sslCertAdaptAlgoritm(ca->alg), ca->param);
        if (ca->aclList)
            dump_acl_list(entry, ca->aclList);
        storeAppendPrintf(entry, "\n");
    }
}