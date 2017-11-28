void
FtpStateData::buildTitleUrl()
{
    title_url = "ftp://";

    if (strcmp(user, "anonymous")) {
        title_url.append(user);
        title_url.append("@");
    }

    title_url.append(request->GetHost());

    if (request->port != urlDefaultPort(PROTO_FTP)) {
        title_url.append(":");
        title_url.append(xitoa(request->port));
    }

    title_url.append (request->urlpath);

    base_href = "ftp://";

    if (strcmp(user, "anonymous") != 0) {
        base_href.append(rfc1738_escape_part(user));

        if (password_url) {
            base_href.append (":");
            base_href.append(rfc1738_escape_part(password));
        }

        base_href.append("@");
    }

    base_href.append(request->GetHost());

    if (request->port != urlDefaultPort(PROTO_FTP)) {
        base_href.append(":");
        base_href.append(xitoa(request->port));
    }

    base_href.append(request->urlpath);
    base_href.append("/");
}