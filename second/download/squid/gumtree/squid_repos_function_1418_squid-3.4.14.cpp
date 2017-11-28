char const *
icpGetUrlToSend(char *url)
{
    if (strpbrk(url, w_space))
        return rfc1738_escape(url);
    else
        return url;
}