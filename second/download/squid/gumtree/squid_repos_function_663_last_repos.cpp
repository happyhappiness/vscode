void HttpMsg::firstLineBuf(MemBuf& mb)
{
    packFirstLineInto(&mb, true);
}