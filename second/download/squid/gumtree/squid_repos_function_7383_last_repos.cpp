bool Security::PeerConnector::doneAll() const
{
    return (!callback || callback->canceled()) && AsyncJob::doneAll();
}