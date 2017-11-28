    return note;
}

Note::Pointer
Notes::parse(ConfigParser &parser)
{
    String key = ConfigParser::NextToken();
    ConfigParser::EnableMacros();
    String value = ConfigParser::NextQuotedToken();
    ConfigParser::DisableMacros();
    bool valueWasQuoted = ConfigParser::LastTokenWasQuoted();
    Note::Pointer note = add(key);
    Note::Value::Pointer noteValue = note->addValue(value);

    String label(key);
    label.append('=');
    label.append(value);
    aclParseAclList(parser, &noteValue->aclList, label.termedBuf());
    if (formattedValues && valueWasQuoted) {
        noteValue->valueFormat =  new Format::Format(descr ? descr : "Notes");
        noteValue->valueFormat->parse(value.termedBuf());
    }
    if (blacklisted) {
        for (int i = 0; blacklisted[i] != NULL; ++i) {
            if (note->key.caseCmp(blacklisted[i]) == 0) {
                fatalf("%s:%d: meta key \"%s\" is a reserved %s name",
                       cfg_filename, config_lineno, note->key.termedBuf(),
                       descr ? descr : "");
