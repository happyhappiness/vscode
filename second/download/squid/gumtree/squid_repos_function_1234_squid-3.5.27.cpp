static void parse_note(Notes *notes)
{
    assert(notes);
    notes->parse(LegacyParser);
}