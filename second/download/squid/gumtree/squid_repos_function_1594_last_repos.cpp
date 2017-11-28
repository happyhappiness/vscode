inline size_t
headersEnd(const SBuf &buf, bool &containsObsFold)
{
    return headersEnd(buf.rawContent(), buf.length(), containsObsFold);
}