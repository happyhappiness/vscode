HttpRequest *
icpGetRequest(char *url, int reqnum, int fd, IpAddress &from)
{
    if (strpbrk(url, w_space)) {
        url = rfc1738_escape(url);
        icpCreateAndSend(ICP_ERR, 0, rfc1738_escape(url), reqnum, 0, fd, from);
        return NULL;
    }

    HttpRequest *result;

    if ((result = HttpRequest::CreateFromUrl(url)) == NULL)
        icpCreateAndSend(ICP_ERR, 0, url, reqnum, 0, fd, from);

    return result;

}