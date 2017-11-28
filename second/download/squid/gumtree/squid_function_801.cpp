void
Adaptation::Config::ParseMetaHeader(ConfigParser &parser)
{
    String name, value;
    const char *warnFor[] = {
        "Methods",
        "Service",
        "ISTag",
        "Encapsulated",
        "Opt-body-type",
        "Max-Connections",
        "Options-TTL",
        "Date",
        "Service-ID",
        "Allow",
        "Preview",
        "Transfer-Preview",
        "Transfer-Ignore",
        "Transfer-Complete",
        NULL
    };
    ConfigParser::ParseString(&name);
    ConfigParser::ParseQuotedString(&value);

    // TODO: Find a way to move this check to ICAP
    for (int i = 0; warnFor[i] != NULL; ++i) {
        if (name.caseCmp(warnFor[i]) == 0) {
            fatalf("%s:%d: meta name \"%s\" is a reserved ICAP header name",
                   cfg_filename, config_lineno, name.termedBuf());
        }
    }

    MetaHeader::Pointer meta = addMetaHeader(name);
    MetaHeader::Value::Pointer headValue = meta->addValue(value);
    aclParseAclList(parser, &headValue->aclList);
}