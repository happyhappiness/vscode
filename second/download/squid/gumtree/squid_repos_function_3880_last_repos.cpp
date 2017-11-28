static void
Ssl::HandleGeneratorReply(void *data, const ::Helper::Reply &reply)
{
    const std::unique_ptr<Ssl::GeneratorRequest> request(static_cast<Ssl::GeneratorRequest*>(data));
    assert(request);
    const auto erased = TheGeneratorRequests.erase(request->query);
    assert(erased);

    for (auto &requestor: request->requestors) {
        if (void *cbdata = requestor.data.validDone()) {
            debugs(83, 5, "to " << cbdata << " in " << *request);
            requestor.callback(cbdata, reply);
        }
    }
}