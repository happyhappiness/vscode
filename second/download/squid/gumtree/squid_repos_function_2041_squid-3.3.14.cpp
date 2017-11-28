bool
StoreMetaSTD::validLength(int len) const
{
    return len == STORE_HDR_METASIZE_OLD;
}