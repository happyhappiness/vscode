void
Ipc::Mem::Segment::create(const off_t aSize)
{
    assert(aSize > 0);
    assert(!theMem);
    checkSupport("Fake segment creation");

    const bool inserted = Segments.insert(std::make_pair(theName, this)).second;
    if (!inserted)
        fatalf("Duplicate fake segment creation: %s", theName.termedBuf());

    theMem = new char[aSize];
    theSize = aSize;
    doUnlink = true;

    debugs(54, 3, HERE << "created " << theName << " fake segment: " << theSize);
}