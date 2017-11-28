Adaptation::History::Pointer
HttpRequest::adaptLogHistory() const
{
    return HttpRequest::adaptHistory(Log::TheConfig.hasAdaptToken);
}