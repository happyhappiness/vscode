void
ACLStringData::parse()
{
    while (const char *t = ConfigParser::strtokFile())
        stringValues.insert(SBuf(t));
}