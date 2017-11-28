const CharacterSet &
Http::One::Parser::DelimiterCharacters()
{
    return Config.onoff.relaxed_header_parser ?
           RelaxedDelimiterCharacters() : CharacterSet::SP;
}