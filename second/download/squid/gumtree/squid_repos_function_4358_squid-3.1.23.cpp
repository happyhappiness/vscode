void
ACL::Initialize()
{
    ACL *a = Config.aclList;
    debugs(53, 3, "ACL::Initialize");

    while (a) {
        a->prepareForUse();
        a = a->next;
    }
}