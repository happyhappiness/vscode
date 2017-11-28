Auth::Config *
Auth::Basic::Scheme::createConfig()
{
    Auth::Basic::Config *newCfg = new Auth::Basic::Config;
    return dynamic_cast<Auth::Config*>(newCfg);
}