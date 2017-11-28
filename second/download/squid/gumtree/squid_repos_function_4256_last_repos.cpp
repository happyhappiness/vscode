bool
ACLSquidErrorData::match(err_type err)
{
    CbDataListIterator<err_type> iter(errors);
    while (!iter.end()) {
        err_type localErr = iter.next();
        debugs(28, 4, "check (" << err << "):"  << errorTypeName(err) << " against " <<  errorTypeName(localErr));
        if (err == localErr)
            return true;
    }

    return false;
}