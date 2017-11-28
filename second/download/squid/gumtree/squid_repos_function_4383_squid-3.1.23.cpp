void
ACLFilledChecklist::conn(ConnStateData *aConn)
{
    assert (conn() == NULL);
    conn_ = cbdataReference(aConn);
}