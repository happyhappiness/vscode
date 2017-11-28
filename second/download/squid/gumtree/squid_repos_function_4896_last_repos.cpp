static const CharacterSet &
RelaxedDelimiterCharacters()
{
    // RFC 7230 section 3.5
    // tolerant parser MAY accept any of SP, HTAB, VT (%x0B), FF (%x0C),
    // or bare CR as whitespace between request-line fields
    static const CharacterSet RelaxedDels =
        (CharacterSet::SP +
         CharacterSet::HTAB +
         CharacterSet("VT,FF","\x0B\x0C") +
         CharacterSet::CR).rename("relaxed-WSP");

    return RelaxedDels;
}