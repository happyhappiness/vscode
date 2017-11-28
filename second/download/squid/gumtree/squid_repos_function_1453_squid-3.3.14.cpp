char const*
HttpRequestMethod::image() const
{
    if (METHOD_OTHER != theMethod) {
        return RequestMethodStr[theMethod];
    } else {
        if (theImage.size()>0) {
            return theImage.termedBuf();
        } else {
            return "METHOD_OTHER";
        }
    }
}