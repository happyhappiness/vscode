static bool
CaseInsensitveSBufCompare(const SBuf &lhs, const SBuf &rhs)
{
    return (lhs.caseCmp(rhs) < 0);
}