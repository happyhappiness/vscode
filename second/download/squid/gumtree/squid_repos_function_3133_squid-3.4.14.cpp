const cache_key *
storeKeyPublicByRequest(HttpRequest * request)
{
    return storeKeyPublicByRequestMethod(request, request->method);
}