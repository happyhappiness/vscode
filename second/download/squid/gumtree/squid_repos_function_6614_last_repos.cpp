void
IcmpConfig::parse()
{
    if (char *token = ConfigParser::NextQuotedOrToEol()) {
        program.clear();
        program.append(token);
    } else
        self_destruct();
}