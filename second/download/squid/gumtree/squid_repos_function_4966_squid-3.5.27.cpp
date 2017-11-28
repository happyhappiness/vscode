void
ACLStringData::parse()
{
    char *t;
    while ((t = strtokFile()))
        stringValues.insert(SBuf(t));
}