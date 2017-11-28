void Adaptation::Icap::ModXact::detailError(int errDetail)
{
    HttpRequest *request = dynamic_cast<HttpRequest*>(adapted.header);
    // if no adapted request, update virgin (and inherit its properties later)
    // TODO: make this and HttpRequest::detailError constant, like adaptHistory
    if (!request)
        request = const_cast<HttpRequest*>(&virginRequest());

    if (request)
        request->detailError(ERR_ICAP_FAILURE, errDetail);
}