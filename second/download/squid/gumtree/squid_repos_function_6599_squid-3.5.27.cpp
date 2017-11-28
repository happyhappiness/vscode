char const *
ESICustomParser::findTag(char const *buffer, size_t bufferLength)
{
    size_t myOffset (0);
    ESITAG_t *resulttype = NULL;

    while (myOffset < bufferLength &&
            (resulttype = static_cast<ESITAG_t *>(GetTrie()->findPrefix (buffer + myOffset, bufferLength - myOffset)))
            == NULL)
        ++myOffset;

    if (myOffset == bufferLength)
        return NULL;

    debugs(86, 9, "ESICustomParser::findTag: found " << *resulttype);

    lastTag = *resulttype;

    return buffer + myOffset;
}