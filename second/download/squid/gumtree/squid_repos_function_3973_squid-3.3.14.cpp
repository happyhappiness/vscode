void
Adaptation::Ecap::XactionRep::visitEachMetaHeader(libecap::NamedValueVisitor &visitor) const
{
    HttpRequest *request = dynamic_cast<HttpRequest*>(theCauseRep ?
                           theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    HttpReply *reply = dynamic_cast<HttpReply*>(theVirginRep.raw().header);

    typedef Adaptation::Config::MetaHeaders::iterator ACAMLI;
    for (ACAMLI i = Adaptation::Config::metaHeaders.begin(); i != Adaptation::Config::metaHeaders.end(); ++i) {
        const char *v = (*i)->match(request, reply);
        if (v) {
            const libecap::Name name((*i)->name.termedBuf());
            const libecap::Area value = libecap::Area::FromTempString(v);
            visitor.visit(name, value);
        }
    }
}