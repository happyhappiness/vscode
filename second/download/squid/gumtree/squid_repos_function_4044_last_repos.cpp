void
ACLSslErrorData::parse()
{
    while (char *t = ConfigParser::strtokFile()) {
        Ssl::ParseErrorString(t, values);
    }
}