static void
parse_client_delay_pool_access(ClientDelayConfig * cfg)
{
    cfg->parsePoolAccess(LegacyParser);
}