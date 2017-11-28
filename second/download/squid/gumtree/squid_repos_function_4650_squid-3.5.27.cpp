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
            bool d3big = (strlen(d3) > strlen(d4)); // Always suggest removing the longer one.
            debugs(28, DBG_IMPORTANT, "WARNING: '" << (d3big?d3:d4) << "' is a subdomain of '" << (d3big?d4:d3) << "'");
            debugs(28, DBG_IMPORTANT, "WARNING: You should remove '" << (d3big?d3:d4) << "' from the ACL named '" << AclMatchedName << "'");
            debugs(28, 2, HERE << "Ignore '" << d3 << "' to keep splay tree searching predictable");
        }
    } else if (ret == 0) {
        // It may be an exact duplicate. No problem. Just drop.
        if (strcmp(d1,d2)==0) {
            debugs(28, 2, "WARNING: '" << d2 << "' is duplicated in the list.");
            debugs(28, 2, "WARNING: You should remove one '" << d2 << "' from the ACL named '" << AclMatchedName << "'");
            return ret;
        }
        // When a.example.com comes before .example.com in an ACL
        // discarding the wildcard is critically bad.
        // or Maybe even both are wildcards. Things are very weird in those cases.
        bool d1big = (strlen(d1) > strlen(d2)); // Always suggest removing the longer one.
        debugs(28, DBG_CRITICAL, "ERROR: '" << (d1big?d1:d2) << "' is a subdomain of '" << (d1big?d2:d1) << "'");
        debugs(28, DBG_CRITICAL, "ERROR: You need to remove '" << (d1big?d1:d2) << "' from the ACL named '" << AclMatchedName << "'");
        self_destruct();
    }

    return ret;
}