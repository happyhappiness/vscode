void
httpRequestPack(void *obj, Packable *p)
{
    HttpRequest *request = static_cast<HttpRequest*>(obj);
    request->pack(p);
}