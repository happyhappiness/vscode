void
ConfigParser::ParseBool(bool *var)
{
    int i = GetInteger();

    if (0 == i)
        *var = false;
    else if (1 == i)
        *var = true;
    else
        self_destruct();
}