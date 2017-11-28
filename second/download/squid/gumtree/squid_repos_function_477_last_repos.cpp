int
HttpReply::httpMsgParseError()
{
    int result(HttpMsg::httpMsgParseError());
    /* indicate an error in the status line */
    sline.set(Http::ProtocolVersion(), Http::scInvalidHeader);
    return result;
}