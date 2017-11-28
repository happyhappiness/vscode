libecap::Area
Adaptation::Ecap::HeaderRep::image() const
{
    MemBuf mb;
    mb.init();

    Packer p;
    packerToMemInit(&p, &mb);
    theMessage.packInto(&p, true);
    packerClean(&p);
    return Area::FromTempBuffer(mb.content(), mb.contentSize());
}