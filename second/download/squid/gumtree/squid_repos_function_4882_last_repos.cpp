Http1::Parser::size_type
Http::One::RequestParser::firstLineSize() const
{
    // RFC 7230 section 2.6
    /* method SP request-target SP "HTTP/" DIGIT "." DIGIT CRLF */
    return method_.image().length() + uri_.length() + 12;
}