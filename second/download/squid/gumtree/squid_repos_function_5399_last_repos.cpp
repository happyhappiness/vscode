const SBuf &
Ftp::UrlWith2f(HttpRequest * request)
{
    SBuf newbuf("%2f");

    if (request->url.getScheme() != AnyP::PROTO_FTP) {
        static const SBuf nil;
        return nil;
    }

    if (request->url.path()[0] == '/') {
        newbuf.append(request->url.path());
        request->url.path(newbuf);
    } else if (!request->url.path().startsWith(newbuf)) {
        newbuf.append(request->url.path().substr(1));
        request->url.path(newbuf);
    }

    return request->effectiveRequestUri();
}