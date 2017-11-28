void Adaptation::Icap::Xaction::callException(const std::exception  &e)
{
    setOutcome(xoError);
    service().noteFailure();
    Adaptation::Initiate::callException(e);
}