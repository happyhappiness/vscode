void
httpRequestPack(void *obj, Packer *p)
{
    HttpRequest *request = static_cast<HttpRequest*>(obj);
    request->pack(p);
}