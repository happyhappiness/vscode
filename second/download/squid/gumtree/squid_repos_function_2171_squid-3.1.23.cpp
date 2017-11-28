void
MemObject::replaceHttpReply(HttpReply *newrep)
{
    HTTPMSGUNLOCK(_reply);
    _reply = HTTPMSGLOCK(newrep);
}