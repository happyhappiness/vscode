void
rfc1035MessageDestroy(rfc1035_message ** msg)
{
    if (!*msg)
        return;
    if ((*msg)->query)
        xfree((*msg)->query);
    if ((*msg)->answer)
        rfc1035RRDestroy(&(*msg)->answer, (*msg)->ancount);
    xfree(*msg);
    *msg = NULL;
}