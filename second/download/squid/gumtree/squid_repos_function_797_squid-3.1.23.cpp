int
HttpReply::httpMsgParseError()
{
    int result(HttpMsg::httpMsgParseError());
    /* indicate an error in the status line */
    sline.status = HTTP_INVALID_HEADER;
    return result;
}