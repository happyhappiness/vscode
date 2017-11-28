bool Adaptation::Service::broken() const
{
    return probed() && !up();
}