bool
ConnStateData::mayTunnelUnsupportedProto()
{
    return Config.accessList.on_unsupported_protocol
#if USE_OPENSSL
           &&
           ((port->flags.isIntercepted() && port->flags.tunnelSslBumping)
            || (serverBump() && pinning.serverConnection))
#endif
           ;
}