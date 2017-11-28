static void
helperStatefulRequestFree(helper_stateful_request * r)
{
    if (r) {
        cbdataReferenceDone(r->data);
        xfree(r->buf);
        delete r;
    }
}