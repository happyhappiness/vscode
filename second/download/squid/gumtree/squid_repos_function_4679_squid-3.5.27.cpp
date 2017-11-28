void
ACLNoteData::parse()
{
    char* t = strtokFile();
    assert (t != NULL);
    name = t;
    values->parse();
}