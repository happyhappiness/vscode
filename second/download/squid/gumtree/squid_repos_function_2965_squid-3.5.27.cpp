Adaptation::History::Pointer
HttpRequest::adaptHistory(bool createIfNone) const
{
    if (!adaptHistory_ && createIfNone) {
        adaptHistory_ = new Adaptation::History();
        debugs(93,4, HERE << "made " << adaptHistory_ << " for " << this);
    }

    return adaptHistory_;
}