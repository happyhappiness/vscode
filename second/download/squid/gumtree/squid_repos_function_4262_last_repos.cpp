void
ACLASN::prepareForUse()
{
    for (CbDataList<int> *i = data; i; i = i->
                                           next)
        asnCacheStart(i->element);
}