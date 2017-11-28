void
clientReplyContext::makeThisHead()
{
    /* At least, I think thats what this does */
    dlinkDelete(&http->active, &ClientActiveRequests);
    dlinkAdd(http, &http->active, &ClientActiveRequests);
}