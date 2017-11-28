int
parseConfigFile(const char *file_name)
{
    try {
        return parseConfigFileOrThrow(file_name);
    }
    catch (const std::exception &ex) {
        debugs(3, DBG_CRITICAL, "FATAL: bad configuration: " << ex.what());
        self_destruct();
        return 1; // not reached
    }
}