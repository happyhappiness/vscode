void
clientReplyDetach(clientStreamNode * node, ClientHttpRequest * http)
{
    /** detach from the stream */
    clientStreamDetach(node, http);
}