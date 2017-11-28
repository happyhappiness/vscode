const char *
MemObject::storeId() const
{
    if (!storeId_.size()) {
        debugs(20, DBG_IMPORTANT, "Bug: Missing MemObject::storeId value");
        dump();
        storeId_ = "[unknown_URI]";
    }
    return storeId_.termedBuf();
}