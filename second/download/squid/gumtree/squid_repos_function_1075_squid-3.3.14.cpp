static void
free_authparam(Auth::ConfigVector * cfg)
{
    /* Wipe the Auth globals and Detach/Destruct component config + state. */
    cfg->clean();

    /* remove our pointers to the probably-dead sub-configs */
    while (cfg->size()) {
        cfg->pop_back();
    }

    /* on reconfigure initialize new auth schemes for the new config. */
    if (reconfiguring) {
        Auth::Init();
    }
}