void
mem_hdr::internalAppend(const char *data, int len)
{
    debugs(19, 6, "memInternalAppend: " << this << " len " << len);

    while (len > 0) {
        makeAppendSpace();
        int copied = appendToNode (nodes.finish()->data, data, len);
        assert (copied);

        len -= copied;
        data += copied;
    }
}