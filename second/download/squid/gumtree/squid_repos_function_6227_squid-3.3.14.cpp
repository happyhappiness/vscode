void
Ipc::TypedMsgHdr::getString(String &s) const
{
    const int length = getInt();
    Must(length >= 0);
    // String uses memcpy uncoditionally; TODO: SBuf eliminates this check
    if (!length) {
        s.clean();
        return;
    }

    Must(length <= maxSize);
    // TODO: use SBuf.reserve() instead of a temporary buffer
    char buf[maxSize];
    getRaw(&buf, length);
    s.limitInit(buf, length);
}