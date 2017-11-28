bool
StoreMetaSTDLFS::validLength(int len) const
{
    return len == STORE_HDR_METASIZE;
}