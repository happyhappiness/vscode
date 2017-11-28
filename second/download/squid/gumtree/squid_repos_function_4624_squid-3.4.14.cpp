ACL *
Acl::NotNode::clone() const
{
    // Not implemented: we are not a named ACL type in squid.conf so nobody
    // should try to create a NotNode instance by ACL type name (which is
    // what clone() API is for -- it does not really clone anything).
    assert(false);
    return NULL;
}