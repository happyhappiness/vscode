const libecap::Area
Adaptation::Ecap::XactionRep::metaValue(const libecap::Name &name) const
{
    HttpRequest *request = dynamic_cast<HttpRequest*>(theCauseRep ?
                           theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    HttpReply *reply = dynamic_cast<HttpReply*>(theVirginRep.raw().header);

    if (name.known()) { // must check to avoid empty names matching unset cfg
        typedef Notes::iterator ACAMLI;
        for (ACAMLI i = Adaptation::Config::metaHeaders.begin(); i != Adaptation::Config::metaHeaders.end(); ++i) {
            if (name == (*i)->key.termedBuf()) {
                if (const char *value = (*i)->match(request, reply, al))
                    return libecap::Area::FromTempString(value);
                else
                    return libecap::Area();
            }
        }
    }

    return libecap::Area();
}