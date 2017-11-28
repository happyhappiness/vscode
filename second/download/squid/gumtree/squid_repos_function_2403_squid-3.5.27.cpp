int64_t
MemObject::expectedReplySize() const
{
    debugs(20, 7, HERE << "object_sz: " << object_sz);
    if (object_sz >= 0) // complete() has been called; we know the exact answer
        return object_sz;

    if (_reply) {
        const int64_t clen = _reply->bodySize(method);
        debugs(20, 7, HERE << "clen: " << clen);
        if (clen >= 0 && _reply->hdr_sz > 0) // yuck: HttpMsg sets hdr_sz to 0
            return clen + _reply->hdr_sz;
    }

    return -1; // not enough information to predict
}