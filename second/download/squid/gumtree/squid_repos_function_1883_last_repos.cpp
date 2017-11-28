void
MemObject::markEndOfReplyHeaders()
{
    const int hdr_sz = endOffset();
    assert(hdr_sz >= 0);
    assert(_reply);
    _reply->hdr_sz = hdr_sz;
}