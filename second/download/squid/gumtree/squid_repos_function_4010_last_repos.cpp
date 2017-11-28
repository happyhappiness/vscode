void
ACLNoteData::parse()
{
    char* t = ConfigParser::strtokFile();
    assert (t != NULL);
    name = t;
    values->parse();
}