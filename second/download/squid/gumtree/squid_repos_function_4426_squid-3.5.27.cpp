std::ostream &
Ssl::Bio::sslFeatures::print(std::ostream &os) const
{
    static std::string buf;
    // TODO: Also print missing features like the HeartBeats and AppLayerProtoNeg
    return os << "v" << sslVersion <<
           " SNI:" << (serverName.isEmpty() ? SBuf("-") : serverName) <<
           " comp:" << compressMethod <<
           " Ciphers:" << clientRequestedCiphers <<
           " Random:" << objToString(client_random, SSL3_RANDOM_SIZE) <<
           " ecPointFormats:" << ecPointFormatList <<
           " ec:" << ellipticCurves <<
           " opaquePrf:" << opaquePrf;
}