Note::Pointer
Notes::parse(ConfigParser &parser)
{
    String key, value;
    ConfigParser::ParseString(&key);
    ConfigParser::ParseQuotedString(&value);
    Note::Pointer note = add(key);
    Note::Value::Pointer noteValue = note->addValue(value);

    String label(key);
    label.append('=');
    label.append(value);
    aclParseAclList(parser, &noteValue->aclList, label.termedBuf());

    if (blacklisted) {
        for (int i = 0; blacklisted[i] != NULL; ++i) {
            if (note->key.caseCmp(blacklisted[i]) == 0) {
                fatalf("%s:%d: meta key \"%s\" is a reserved %s name",
                       cfg_filename, config_lineno, note->key.termedBuf(),
                       descr ? descr : "");
            }
        }
    }

    return note;
}