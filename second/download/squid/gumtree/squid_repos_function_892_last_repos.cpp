static void free_sslproxy_cert_sign(sslproxy_cert_sign **cert_sign)
{
    while (*cert_sign) {
        sslproxy_cert_sign *cs = *cert_sign;
        *cert_sign = cs->next;

        if (cs->aclList)
            aclDestroyAclList(&cs->aclList);

        safe_free(cs);
    }
}