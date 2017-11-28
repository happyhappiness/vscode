std::size_t
CaseInsensitiveSBufHash::operator() (const SBuf & sbuf) const noexcept
{
    return SBufHashCommon_(sbuf, true);
}