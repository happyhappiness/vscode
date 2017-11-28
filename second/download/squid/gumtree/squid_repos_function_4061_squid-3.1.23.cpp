void Adaptation::Icap::Options::TransferList::parse(const String &buf, bool &foundStar)
{
    foundStar = false;

    const char *item;
    const char *pos = NULL;
    int ilen;
    while (strListGetItem(&buf, ',', &item, &ilen, &pos)) {
        if (ilen == 1 && *item == '*')
            foundStar = true;
        else
            add(xstrndup(item, ilen+1));
    }
}