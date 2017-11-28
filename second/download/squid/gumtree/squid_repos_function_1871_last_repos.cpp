const char *
MemObject::logUri() const
{
    return logUri_.size() ? logUri_.termedBuf() : storeId();
}