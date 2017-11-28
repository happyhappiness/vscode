void Adaptation::Icap::Xaction::noteCommTimedout(const CommTimeoutCbParams &)
{
    handleCommTimedout();
}