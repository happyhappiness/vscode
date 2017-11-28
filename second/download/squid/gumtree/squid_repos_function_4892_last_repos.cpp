bool
Http::One::RequestParser::parse(const SBuf &aBuf)
{
    const bool result = doParse(aBuf);
    if (preserveParsed_) {
        assert(aBuf.length() >= remaining().length());
        parsed_.append(aBuf.substr(0, aBuf.length() - remaining().length())); // newly parsed bytes
    }

    return result;
}