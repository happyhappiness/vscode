const CharacterSet &
Http::One::RequestParser::RequestTargetCharacters()
{
    if (Config.onoff.relaxed_header_parser) {
#if USE_HTTP_VIOLATIONS
        static const CharacterSet RelaxedExtended =
            UriValidCharacters() +
            // accept whitespace (extended), it will be dealt with later
            DelimiterCharacters() +
            // RFC 2396 unwise character set which must never be transmitted
            // in un-escaped form. But many web services do anyway.
            CharacterSet("RFC2396-unwise","\"\\|^<>`{}") +
            // UTF-8 because we want to be future-proof
            CharacterSet("UTF-8", 128, 255);

        return RelaxedExtended;
#else
        static const CharacterSet RelaxedCompliant =
            UriValidCharacters() +
            // accept whitespace (extended), it will be dealt with later.
            DelimiterCharacters();

        return RelaxedCompliant;
#endif
    }

    // strict parse only accepts what the RFC say we can
    return UriValidCharacters();
}