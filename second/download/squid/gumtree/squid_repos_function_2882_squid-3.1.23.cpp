Adaptation::Icap::History::Pointer
HttpRequest::icapHistory() const
{
    if (!icapHistory_) {
        if ((LogfileStatus == LOG_ENABLE && alLogformatHasIcapToken) ||
                IcapLogfileStatus == LOG_ENABLE) {
            icapHistory_ = new Adaptation::Icap::History();
            debugs(93,4, HERE << "made " << icapHistory_ << " for " << this);
        }
    }

    return icapHistory_;
}