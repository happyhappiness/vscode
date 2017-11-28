bool
Http::ContentLengthInterpreter::goodSuffix(const char *suffix, const char * const end) const
{
    // optimize for the common case that does not need delimiters
    if (suffix == end)
        return true;

    for (const CharacterSet &delimiters = Http::One::Parser::DelimiterCharacters();
            suffix < end; ++suffix) {
        if (!delimiters[*suffix])
            return false;
    }
    // needsSanitizing = true; // TODO: Always remove trailing whitespace?
    return true; // including empty suffix
}