{
    debugs(28, 3, "freeing ACL " << name);
    safe_free(cfgline);
    AclMatchedName = NULL; // in case it was pointing to our name
}

void
ACL::Initialize()
{
    ACL *a = Config.aclList;
    debugs(53, 3, "ACL::Initialize");

