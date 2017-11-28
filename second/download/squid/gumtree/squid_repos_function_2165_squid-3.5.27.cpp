long
cbdata::MakeOffset()
{
    cbdata *zero = (cbdata *)0L;
    void **dataOffset = &zero->data;
    return (long)dataOffset;
}