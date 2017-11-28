bool
Auth::Negotiate::Config::active() const
{
    return authnegotiate_initialised == 1;
}