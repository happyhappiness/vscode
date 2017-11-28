bool
Adaptation::Ecap::XactionRep::doneAll() const
{
    return makingVb >= opComplete && proxyingAb >= opComplete &&
           Adaptation::Initiate::doneAll();
}