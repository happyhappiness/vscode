void
ConfigParser::ParseQuotedString(char **var, bool *wasQuoted)
{
    if (const char *phrase = NextElement(wasQuoted))
        *var = xstrdup(phrase);
    else
        self_destruct();
}