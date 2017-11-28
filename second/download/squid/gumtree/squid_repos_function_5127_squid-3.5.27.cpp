bool
Rock::SwapDir::doReportStat() const
{
    return ::SwapDir::doReportStat() && (!UsingSmp() || IamDiskProcess());
}