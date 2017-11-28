void
HttpHeader::refreshMask()
{
    httpHeaderMaskInit(&mask, 0);
    debugs(55, 7, "refreshing the mask in hdr " << this);
    HttpHeaderPos pos = HttpHeaderInitPos;
    while (HttpHeaderEntry *e = getEntry(&pos)) {
        CBIT_SET(mask, e->id);
    }
}