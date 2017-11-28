const SBuf &
HttpRequestMethod::image() const
{
    static const SBuf methodOther("METHOD_OTHER");
    if (Http::METHOD_OTHER != theMethod) {
        return Http::MethodType_sb[theMethod];
    } else {
        if (!theImage.isEmpty()) {
            return theImage;
        } else {
            return methodOther;
        }
    }
}