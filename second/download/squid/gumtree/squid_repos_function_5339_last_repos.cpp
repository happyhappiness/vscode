void
Ftp::Gateway::buildTitleUrl()
{
    title_url = "ftp://";

    if (strcmp(user, "anonymous")) {
        title_url.append(user);
        title_url.append("@");
    }

    SBuf authority = request->url.authority(request->url.getScheme() != AnyP::PROTO_FTP);

    title_url.append(authority.rawContent(), authority.length());
    title_url.append(request->url.path().rawContent(), request->url.path().length());

    base_href = "ftp://";

    if (strcmp(user, "anonymous") != 0) {
        base_href.append(rfc1738_escape_part(user));

        if (password_url) {
            base_href.append(":");
            base_href.append(rfc1738_escape_part(password));
        }

        base_href.append("@");
    }

    base_href.append(authority.rawContent(), authority.length());
    base_href.append(request->url.path().rawContent(), request->url.path().length());
    base_href.append("/");
}