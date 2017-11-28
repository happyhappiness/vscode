SBufList
ACLASN::dump() const
{
    SBufList sl;

    CbDataList<int> *ldata = data;

    while (ldata != NULL) {
        SBuf s;
        s.Printf("%d", ldata->element);
        sl.push_back(s);
        ldata = ldata->next;
    }

    return sl;
}