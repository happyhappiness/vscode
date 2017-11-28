char const*
HttpRequestMethod::image() const
{
    if (Http::METHOD_OTHER != theMethod) {
        return Http::MethodType_str[theMethod];
    } else {
        if (theImage.size()>0) {
            return theImage.termedBuf();
        } else {
            return "METHOD_OTHER";
        }
    }
}