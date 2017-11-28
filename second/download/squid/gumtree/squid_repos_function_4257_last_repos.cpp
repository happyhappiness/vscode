SBufList
ACLSquidErrorData::dump() const
{
    SBufList sl;
    CbDataListIterator<err_type> iter(errors);
    while (!iter.end()) {
        err_type err = iter.next();
        const char *errName = errorTypeName(err);
        sl.push_back(SBuf(errName));
    }

    return sl;
}