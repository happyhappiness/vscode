Adaptation::Config::MetaHeader::Pointer
Adaptation::Config::addMetaHeader(const String &headerName)
{
    typedef MetaHeaders::iterator AMLI;
    for (AMLI i = metaHeaders.begin(); i != metaHeaders.end(); ++i) {
        if ((*i)->name == headerName)
            return (*i);
    }

    MetaHeader::Pointer meta = new MetaHeader(headerName);
    metaHeaders.push_back(meta);
    return meta;
}