bool
ConfigParser::NextKvPair(char * &key, char * &value)
{
    key = value = NULL;
    ParseKvPair_ = true;
    KvPairState_ = ConfigParser::atParseKey;
    if ((key = NextToken()) != NULL) {
        KvPairState_ = ConfigParser::atParseValue;
        value = NextQuotedToken();
    }
    ParseKvPair_ = false;

    if (!key)
        return false;
    if (!value) {
        debugs(3, DBG_CRITICAL, "Error while parsing key=value token. Value missing after: " << key);
        return false;
    }

    return true;
}