void
Ipc::Mem::Segment::open()
{
    assert(!theMem);
    checkSupport("Fake segment open");

    const SegmentMap::const_iterator i = Segments.find(theName);
    if (i == Segments.end())
        fatalf("Fake segment not found: %s", theName.termedBuf());

    const Segment &segment = *i->second;
    theMem = segment.theMem;
    theSize = segment.theSize;

    debugs(54, 3, HERE << "opened " << theName << " fake segment: " << theSize);
}