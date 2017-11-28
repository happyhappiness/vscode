void Adaptation::Icap::Xaction::callException(const std::exception  &e)
{
    setOutcome(xoError);
    Adaptation::Initiate::callException(e);
}