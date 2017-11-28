static std::size_t
SBufHashCommon_ (const SBuf & sbuf, bool caseInsensitive) noexcept
{
    //ripped and adapted from hash_string
    const char *s = sbuf.rawContent();
    size_t rv = 0;
    SBuf::size_type len=sbuf.length();
    while (len != 0) {
        rv ^= 271 * (caseInsensitive? xtolower(*s) : *s);
        ++s;
        --len;
    }
    return rv ^ (sbuf.length() * 271);
}