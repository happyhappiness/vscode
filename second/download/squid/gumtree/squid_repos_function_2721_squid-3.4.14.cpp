void
ConfigParser::strtokFileUndo()
{
    assert(lastToken);
    undo.push(lastToken);
}