void
ConfigParser::ParseQuotedString(char **var, bool *wasQuoted)
{
    String sVar;
    ParseQuotedString(&sVar, wasQuoted);
    *var = xstrdup(sVar.termedBuf());
}