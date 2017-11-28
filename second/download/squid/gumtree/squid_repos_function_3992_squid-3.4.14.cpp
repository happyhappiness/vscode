const libecap::Area
Adaptation::Ecap::XactionRep::masterxSharedValue(const libecap::Name &name) const
{
    const HttpRequest *request = dynamic_cast<const HttpRequest*>(theCauseRep ?
                                 theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);
    if (name.known()) { // must check to avoid empty names matching unset cfg
        Adaptation::History::Pointer ah = request->adaptHistory(false);
        if (ah != NULL) {
            String name, value;
            if (ah->getXxRecord(name, value))
                return libecap::Area::FromTempBuffer(value.rawBuf(), value.size());
        }
    }
    return libecap::Area();
}