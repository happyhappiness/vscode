void
Http::One::Server::proceedAfterBodyContinuation(Http::StreamPointer context)
{
    debugs(33, 5, "Body Continuation written");
    clientProcessRequest(this, parser_, context.getRaw());
}