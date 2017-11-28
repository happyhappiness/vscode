}
#endif

void
ServerStateData::sendBodyIsTooLargeError()
{
    ErrorState *err = new ErrorState(ERR_TOO_BIG, Http::scForbidden, request);
    fwd->fail(err);
    fwd->dontRetry(true);
    abortTransaction("Virgin body too large.");
}

// TODO: when HttpStateData sends all errors to ICAP,
