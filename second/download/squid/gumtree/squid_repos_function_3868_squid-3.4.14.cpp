Adaptation::ServiceFilter &Adaptation::ServiceFilter::operator =(const ServiceFilter &f)
{
    if (this != &f) {
        method = f.method;
        point = f.point;
        HTTPMSGUNLOCK(request);
        HTTPMSGUNLOCK(reply);
        request = f.request;
        HTTPMSGLOCK(request);
        reply = f.reply;
        if (reply)
            HTTPMSGLOCK(reply);
    }
    return *this;
}