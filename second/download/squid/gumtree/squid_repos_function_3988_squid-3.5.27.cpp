void
Adaptation::Ecap::HeaderRep::visitEach(libecap::NamedValueVisitor &visitor) const
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    while (HttpHeaderEntry *e = theHeader.getEntry(&pos)) {
        const Name name(e->name.termedBuf()); // optimize: find std Names
        name.assignHostId(e->id);
        visitor.visit(name, Value(e->value.rawBuf(), e->value.size()));
    }
}