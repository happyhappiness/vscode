static void
free_authparam(Auth::ConfigVector * cfg)
{
    /* Wipe the Auth globals and Detach/Destruct component config + state. */
    cfg->clear();

    /* on reconfigure initialize new auth schemes for the new config. */
    if (reconfiguring) {
        Auth::Init();
    }
}