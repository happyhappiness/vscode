bool
Auth::Digest::Config::active() const
{
    return authdigest_initialised == 1;
}