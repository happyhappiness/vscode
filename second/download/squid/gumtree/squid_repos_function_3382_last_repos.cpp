libecap::Area
Adaptation::Ecap::HeaderRep::image() const
{
    MemBuf mb;
    mb.init();
    theMessage.packInto(&mb, true);
    return Area::FromTempBuffer(mb.content(), mb.contentSize());
}