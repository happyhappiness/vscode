MemBuf *
HttpReply::pack()
{
    MemBuf *mb = new MemBuf;
    Packer p;

    mb->init();
    packerToMemInit(&p, mb);
    packInto(&p);
    packerClean(&p);
    return mb;
}