static int
clientIsContentLengthValid(HttpRequest * r)
{
    switch (r->method.id()) {

    case Http::METHOD_GET:

    case Http::METHOD_HEAD:
        /* We do not want to see a request entity on GET/HEAD requests */
        return (r->content_length <= 0 || Config.onoff.request_entities);

    default:
        /* For other types of requests we don't care */
        return 1;
    }

    /* NOT REACHED */
}