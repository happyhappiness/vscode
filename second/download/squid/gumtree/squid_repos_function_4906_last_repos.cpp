bool
Http::One::ParseBws(Tokenizer &tok)
{
    if (const auto count = tok.skipAll(Parser::WhitespaceCharacters())) {
        // Generating BWS is a MUST-level violation so warn about it as needed.
        debugs(33, ErrorLevel(), "found " << count << " BWS octets");
        // RFC 7230 says we MUST parse BWS, so we fall through even if
        // Config.onoff.relaxed_header_parser is off.
    }
    // else we successfully "parsed" an empty BWS sequence

    return true;
}