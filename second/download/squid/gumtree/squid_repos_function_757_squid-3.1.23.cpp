void
ClientHttpRequest::httpStart()
{
    PROF_start(httpStart);
    logType = LOG_TAG_NONE;
    debugs(85, 4, "ClientHttpRequest::httpStart: " << log_tags[logType] << " for '" << uri << "'");

    /* no one should have touched this */
    assert(out.offset == 0);
    /* Use the Stream Luke */
    clientStreamNode *node = (clientStreamNode *)client_stream.tail->data;
    clientStreamRead(node, this, node->readBuffer);
    PROF_stop(httpStart);
}