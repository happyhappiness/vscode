static void
parse_memcachemode(SquidConfig * config)
{
    char *token = ConfigParser::NextToken();
    if (!token)
        self_destruct();

    if (strcmp(token, "always") == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 1;
    } else if (strcmp(token, "disk") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 1;
    } else if (strncmp(token, "net", 3) == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 0;
    } else if (strcmp(token, "never") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 0;
    } else {
        debugs(0, DBG_PARSE_NOTE(2), "ERROR: Invalid option '" << token << "': 'memory_cache_mode' accepts 'always', 'disk', 'network', and 'never'.");
        self_destruct();
    }
}