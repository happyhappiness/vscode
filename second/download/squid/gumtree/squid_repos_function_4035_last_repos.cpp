static bool
CaseSensitiveSBufCompare(const SBuf &lhs, const SBuf &rhs)
{
    return (lhs.cmp(rhs) < 0);
}