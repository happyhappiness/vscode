void
ACLMaxConnection::prepareForUse()
{
    if (0 != Config.onoff.client_db)
        return;

    debugs(22, DBG_CRITICAL, "WARNING: 'maxconn' ACL (" << name << ") won't work with client_db disabled");
}