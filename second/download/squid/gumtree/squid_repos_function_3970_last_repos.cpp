void
Acl::TransactionInitiator::parse()
{
    while (const char *s = ConfigParser::strtokFile()) {
        initiators_ |= XactionInitiator::ParseInitiators(s);
        cfgWords.push_back(SBuf(s));
    }
}