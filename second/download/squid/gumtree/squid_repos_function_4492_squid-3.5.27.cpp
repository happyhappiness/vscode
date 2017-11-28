static bool
isSslServer()
{
    if (HttpsPortList != NULL)
        return true;

    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (s->flags.tunnelSslBumping)
            return true;
    }

    return false;
}