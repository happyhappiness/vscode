bool
AcceptLimiter::deferring() const
{
    return deferred.size() > 0;
}