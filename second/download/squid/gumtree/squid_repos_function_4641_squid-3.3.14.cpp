void *
ACLFilledChecklist::operator new (size_t size)
{
    assert (size == sizeof(ACLFilledChecklist));
    CBDATA_INIT_TYPE(ACLFilledChecklist);
    ACLFilledChecklist *result = cbdataAlloc(ACLFilledChecklist);
    return result;
}