void
ConfigParser::ParseQuotedString(String *var, bool *wasQuoted)
{
    if (const char *phrase = NextElement(wasQuoted))
        var->reset(phrase);
    else
        self_destruct();
}