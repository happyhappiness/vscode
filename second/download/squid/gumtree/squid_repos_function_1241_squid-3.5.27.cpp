static void
dump_configuration_includes_quoted_values(StoreEntry *const entry, const char *const name, bool recognizeQuotedValues)
{
    int val = ConfigParser::RecognizeQuotedValues ? 1 : 0;
    dump_onoff(entry, name, val);
}