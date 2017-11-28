void
Acl::ConnectionsEncrypted::parse()
{
    if (ConfigParser::strtokFile()) {
        debugs(89, DBG_CRITICAL, "WARNING: connections_encrypted does not accepts any value.");
    }
}