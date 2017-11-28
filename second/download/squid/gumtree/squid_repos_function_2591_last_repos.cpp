const cache_key *
storeKeyPublicByRequest(HttpRequest * request, const KeyScope keyScope)
{
    return storeKeyPublicByRequestMethod(request, request->method, keyScope);
}