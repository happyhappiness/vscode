void
ACLFilledChecklist::conn(ConnStateData *aConn)
{
    if (conn() == aConn)
        return;
    assert (conn() == NULL);
    conn_ = cbdataReference(aConn);
}