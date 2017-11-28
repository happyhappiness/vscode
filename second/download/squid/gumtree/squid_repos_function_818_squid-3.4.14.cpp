int
HttpReply::httpMsgParseError()
{
    int result(HttpMsg::httpMsgParseError());
    /* indicate an error in the status line */
    sline.set(Http::ProtocolVersion(1,1), Http::scInvalidHeader);
    return result;
}