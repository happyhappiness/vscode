inline void
SBufToCstring(char *d, const SBuf &s)
{
    s.copy(d, s.length());
    d[s.length()] = '\0'; // 0-terminate the destination
    debugs(1, DBG_DATA, "built c-string '" << d << "' from " << s);
}