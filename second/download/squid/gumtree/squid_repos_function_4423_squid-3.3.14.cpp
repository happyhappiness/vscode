bool
ACLMethodData::match(HttpRequestMethod toFind)
{
    return values->findAndTune(toFind);
}