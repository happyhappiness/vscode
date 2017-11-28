void
Adaptation::Ecap::XactionRep::visitEachMetaHeader(libecap::NamedValueVisitor &visitor) const
{
    HttpRequest *request = dynamic_cast<HttpRequest*>(theCauseRep ?
                           theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    HttpReply *reply = dynamic_cast<HttpReply*>(theVirginRep.raw().header);

    typedef Notes::iterator ACAMLI;
    for (ACAMLI i = Adaptation::Config::metaHeaders.begin(); i != Adaptation::Config::metaHeaders.end(); ++i) {
        const char *v = (*i)->match(request, reply, al);
        if (v) {
            const libecap::Name name((*i)->key.termedBuf());
            const libecap::Area value = libecap::Area::FromTempString(v);
            visitor.visit(name, value);
        }
    }
}