void
esiChoose::provideData (ESISegment::Pointer data, ESIElement*source)
{
    checkValidSource (source);
    parent->provideData (data, this);
}