void
ConfigParser::TokenPutBack(const char *tok)
{
    assert(tok);
    Undo_.push(tok);
}