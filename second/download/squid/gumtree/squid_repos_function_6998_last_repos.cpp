void
Ipc::TypedMsgHdr::putString(const String &s)
{
    Must(s.psize() <= maxSize);
    putInt(s.psize());
    putRaw(s.rawBuf(), s.psize());
}