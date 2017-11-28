void
Format::FmtConfig::registerTokens(const String &nsName, TokenTableEntry const *tokenArray)
{
    debugs(46, 2, HERE << " register format tokens for '" << nsName << "'");
    if (tokenArray != NULL)
        tokens.push_back(TokenNamespace(nsName, tokenArray));
    else
        debugs(0, DBG_CRITICAL, "BUG: format tokens for '" << nsName << "' missing!");
}