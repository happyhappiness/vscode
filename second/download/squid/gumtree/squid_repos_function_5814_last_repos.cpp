bool
Auth::Basic::Config::active() const
{
    return authbasic_initialised == 1;
}