void HttpMsg::firstLineBuf(MemBuf& mb)
{
    Packer p;
    packerToMemInit(&p, &mb);
    packFirstLineInto(&p, true);
    packerClean(&p);
}