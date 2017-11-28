bool Adaptation::Icap::ServiceRep::hasOptions() const
{
    return theOptions && theOptions->valid() && theOptions->fresh();
}