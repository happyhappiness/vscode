template<class T>
int
aclDomainCompare(T const &a, T const &b)
{
    char * const d1 = static_cast<char *>(b);
    char * const d2 = static_cast<char *>(a);
    int ret;
    ret = aclHostDomainCompare(d1, d2);

    if (ret != 0) {
        char *const d3 = d2;
        char *const d4 = d1;
        ret = aclHostDomainCompare(d3, d4);
        if (ret == 0) {
            // When a.example.com comes after .example.com in an ACL
            // sub-domain is ignored. That is okay. Just important
            debugs(28, DBG_IMPORTANT, "WARNING: '" << d3 << "' is a subdomain of '" << d4 << "'");
            debugs(28, DBG_IMPORTANT, "WARNING: because of this '" << d3 << "' is ignored to keep splay tree searching predictable");
            debugs(28, DBG_IMPORTANT, "WARNING: You should remove '" << (*d3=='.'?d4:d3) << "' from the ACL named '" << AclMatchedName << "'");
        }
    } else if (ret == 0) {
        // When a.example.com comes before .example.com in an ACL
        // discarding the wildcard is critically bad.
        debugs(28, DBG_CRITICAL, "ERROR: '" << d1 << "' is a subdomain of '" << d2 << "'");
        debugs(28, DBG_CRITICAL, "ERROR: because of this '" << d2 << "' is ignored to keep splay tree searching predictable");
        debugs(28, DBG_CRITICAL, "ERROR: You should remove '" << (*d1=='.'?d2:d1) << "' from the ACL named '" << AclMatchedName << "'");
        self_destruct();
    }

    return ret;
}