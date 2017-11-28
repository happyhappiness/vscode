bool
ESIVariableProcessor::validChar (char c)
{
    if (('A' <= c && c <= 'Z') ||
            ('a' <= c && c <= 'z') ||
            '_' == c || '-' == c)
        return true;

    return false;
}