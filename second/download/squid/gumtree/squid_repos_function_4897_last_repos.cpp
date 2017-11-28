const CharacterSet &
Http::One::Parser::WhitespaceCharacters()
{
    return Config.onoff.relaxed_header_parser ?
           RelaxedDelimiterCharacters() : CharacterSet::WSP;
}