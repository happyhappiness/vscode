void
free_denyinfo(AclDenyInfoList ** list)
{
    delete *list;
    *list = nullptr;
}