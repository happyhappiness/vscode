bool
Http::One::Parser::skipLineTerminator(Http1::Tokenizer &tok) const
{
    if (tok.skip(Http1::CrLf()))
        return true;

    if (Config.onoff.relaxed_header_parser && tok.skipOne(CharacterSet::LF))
        return true;

    if (tok.atEnd() || (tok.remaining().length() == 1 && tok.remaining().at(0) == '\r'))
        return false; // need more data

    throw TexcHere("garbage instead of CRLF line terminator");
    return false; // unreachable, but make naive compilers happy
}