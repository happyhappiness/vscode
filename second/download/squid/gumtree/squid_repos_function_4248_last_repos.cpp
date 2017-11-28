ConnStateData *
ACLFilledChecklist::conn() const
{
    return cbdataReferenceValid(conn_) ? conn_ : nullptr;
}