Auth::Config *
Auth::Negotiate::Scheme::createConfig()
{
    Auth::Negotiate::Config *negotiateCfg = new Auth::Negotiate::Config;
    return dynamic_cast<Auth::Config*>(negotiateCfg);
}