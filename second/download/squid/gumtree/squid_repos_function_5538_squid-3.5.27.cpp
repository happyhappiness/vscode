const char *
Ftp::UrlWith2f(HttpRequest * request)
{
    String newbuf = "%2f";

    if (request->url.getScheme() != AnyP::PROTO_FTP)
        return NULL;

    if ( request->urlpath[0]=='/' ) {
        newbuf.append(request->urlpath);
        request->urlpath.absorb(newbuf);
        safe_free(request->canonical);
    } else if ( !strncmp(request->urlpath.termedBuf(), "%2f", 3) ) {
        newbuf.append(request->urlpath.substr(1,request->urlpath.size()));
        request->urlpath.absorb(newbuf);
        safe_free(request->canonical);
    }

    return urlCanonical(request);
}