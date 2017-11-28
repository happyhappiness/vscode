int
ACL::cacheMatchAcl(dlink_list * cache, ACLChecklist *checklist)
{
    acl_proxy_auth_match_cache *auth_match;
    dlink_node *link;
    link = cache->head;

    while (link) {
        auth_match = (acl_proxy_auth_match_cache *)link->data;

        if (auth_match->acl_data == this) {
            debugs(28, 4, "ACL::cacheMatchAcl: cache hit on acl '" << name << "' (" << this << ")");
            return auth_match->matchrv;
        }

        link = link->next;
    }

    auth_match = new acl_proxy_auth_match_cache();
    auth_match->matchrv = matchForCache (checklist);
    auth_match->acl_data = this;
    dlinkAddTail(auth_match, &auth_match->link, cache);
    debugs(28, 4, "ACL::cacheMatchAcl: miss for '" << name << "'. Adding result " << auth_match->matchrv);
    return auth_match->matchrv;
}