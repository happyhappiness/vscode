std::size_t
std::hash<SBuf>::operator() (const SBuf & sbuf) const noexcept
{
    return SBufHashCommon_(sbuf, false);
}