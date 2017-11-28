void Adaptation::Icap::ModXact::clearError()
{
    HttpRequest *request = dynamic_cast<HttpRequest*>(adapted.header);
    // if no adapted request, update virgin (and inherit its properties later)
    if (!request)
        request = const_cast<HttpRequest*>(&virginRequest());

    if (request)
        request->clearError();
}