Http1::Parser::size_type
Http::One::ResponseParser::firstLineSize() const
{
    Http1::Parser::size_type result = 0;

    switch (msgProtocol_.protocol)
    {
    case AnyP::PROTO_HTTP:
        result += Http1magic.length();
        break;
    case AnyP::PROTO_ICY:
        result += IcyMagic.length();
        break;
    default: // no other protocols supported
        return result;
    }
    // NP: the parser does not accept >2 DIGIT for version numbers
    if (msgProtocol_.minor > 9)
        result += 2;
    else
        result += 1;

    result += 5; /* 5 octets in: SP status SP */
    result += reasonPhrase_.length();
    result += 2; /* CRLF terminator */
    return result;
}