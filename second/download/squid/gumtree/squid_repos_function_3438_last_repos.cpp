static SBuf
EssentialVersion(const SBuf &raw)
{
    // all libecap x.y.* releases are supposed to be compatible so we strip
    // everything after the second period
    const SBuf::size_type minorPos = raw.find('.');
    const SBuf::size_type microPos = minorPos == SBuf::npos ?
                                     SBuf::npos : raw.find('.', minorPos+1);
    return raw.substr(0, microPos); // becomes raw if microPos is npos
}