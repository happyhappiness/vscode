static bool
isTlsServer()
{
    for (AnyP::PortCfgPointer s = HttpPortList; s != nullptr; s = s->next) {
        if (s->secure.encryptTransport)
            return true;
        if (s->flags.tunnelSslBumping)
            return true;
    }

    return false;
}