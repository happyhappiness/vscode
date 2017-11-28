static void
downloaderDetach(clientStreamNode * node, ClientHttpRequest * http)
{
    debugs(33, 5, MYNAME);
    clientStreamDetach(node, http);
}