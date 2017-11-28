void
HttpHeader::refreshMask()
{
    httpHeaderMaskInit(&mask, 0);
    debugs(55, 7, "refreshing the mask in hdr " << this);
    for (auto e : entries) {
        if (e)
            CBIT_SET(mask, e->id);
    }
}