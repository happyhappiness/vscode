bool
Adaptation::Ecap::XactionRep::doneAll() const
{
    return proxyingVb >= opComplete && proxyingAb >= opComplete &&
           Adaptation::Initiate::doneAll();
}