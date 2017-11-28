static void
helperRequestFree(helper_request * r)
{
    cbdataReferenceDone(r->data);
    xfree(r->buf);
    delete r;
}