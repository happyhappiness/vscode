void
HttpReply::clean()
{
    // we used to assert that the pipe is NULL, but now the message only
    // points to a pipe that is owned and initiated by another object.
    body_pipe = NULL;

    httpBodyClean(&body);
    hdrCacheClean();
    header.clean();
    httpStatusLineClean(&sline);
    bodySizeMax = -2; // hack: make calculatedBodySizeMax() false
}