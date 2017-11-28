HttpReply *
ServerStateData::setVirginReply(HttpReply *rep)
{
    debugs(11,5, HERE << this << " setting virgin reply to " << rep);
    assert(!theVirginReply);
    assert(rep);
    theVirginReply = HTTPMSGLOCK(rep);
    return theVirginReply;
}