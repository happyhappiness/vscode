SBuf
httpHeaderQuoteString(const char *raw)
{
    assert(raw);

    // TODO: Optimize by appending a sequence of characters instead of a char.
    // This optimization may be easier with Tokenizer after raw becomes SBuf.

    // RFC 7230 says a "sender SHOULD NOT generate a quoted-pair in a
    // quoted-string except where necessary" (i.e., DQUOTE and backslash)
    bool needInnerQuote = false;
    for (const char *s = raw; !needInnerQuote &&  *s; ++s)
        needInnerQuote = *s == '"' || *s == '\\';

    SBuf quotedStr;
    quotedStr.append('"');

    if (needInnerQuote) {
        for (const char *s = raw; *s; ++s) {
            if (*s == '"' || *s == '\\')
                quotedStr.append('\\');
            quotedStr.append(*s);
        }
    } else {
        quotedStr.append(raw);
    }

    quotedStr.append('"');
    return quotedStr;
}