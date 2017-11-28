bool Adaptation::Icap::ServiceRep::needNewOptions() const
{
    return !detached() && !up();
}