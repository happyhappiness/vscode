void
clientReplyContext::operator delete (void *address)
{
    clientReplyContext * tmp = (clientReplyContext *)address;
    cbdataFree (tmp);
}