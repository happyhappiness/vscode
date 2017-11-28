void
ConfigParser::strtokFilePutBack(const char *tok)
{
    assert(tok);
    undo.push(tok);
}