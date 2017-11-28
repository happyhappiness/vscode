void
MemObject::replaceHttpReply(HttpReply *newrep)
{
    HTTPMSGUNLOCK(_reply);
    _reply = newrep;
    HTTPMSGLOCK(_reply);
}