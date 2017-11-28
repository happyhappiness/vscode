Auth::Config *
Auth::Digest::Scheme::createConfig()
{
    Auth::Digest::Config *digestCfg = new Auth::Digest::Config;
    return dynamic_cast<Auth::Config*>(digestCfg);
}