static void free_sslproxy_cert_adapt(sslproxy_cert_adapt **cert_adapt)
{
    while (*cert_adapt) {
        sslproxy_cert_adapt *ca = *cert_adapt;
        *cert_adapt = ca->next;
        safe_free(ca->param);

        if (ca->aclList)
            aclDestroyAclList(&ca->aclList);

        safe_free(ca);
    }
}