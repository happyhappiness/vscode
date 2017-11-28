bool
store_client::memReaderHasLowerOffset(int64_t anOffset) const
{
    return getType() == STORE_MEM_CLIENT && copyInto.offset < anOffset;
}