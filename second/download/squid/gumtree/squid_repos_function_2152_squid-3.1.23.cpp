void
ServerStateData::sendBodyIsTooLargeError()
{
    ErrorState *err = errorCon(ERR_TOO_BIG, HTTP_FORBIDDEN, request);
    err->xerrno = errno;
    fwd->fail(err);
    fwd->dontRetry(true);
    abortTransaction("Virgin body too large.");
}