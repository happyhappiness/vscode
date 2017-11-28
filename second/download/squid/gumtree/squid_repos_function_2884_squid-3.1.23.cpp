Adaptation::History::Pointer
HttpRequest::adaptLogHistory() const
{
    const bool loggingNeedsHistory = (LogfileStatus == LOG_ENABLE) &&
                                     alLogformatHasAdaptToken; // TODO: make global to remove this method?
    return HttpRequest::adaptHistory(loggingNeedsHistory);
}