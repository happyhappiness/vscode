bool
ACLStringData::match(char const *toFind)
{
    return match(SBuf(toFind));
}