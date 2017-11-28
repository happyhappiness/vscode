void
Ftp::Server::calcUri(const SBuf *file)
{
    uri = "ftp://";
    uri.append(host);
    if (port->ftp_track_dirs && master->workingDir.length()) {
        if (master->workingDir[0] != '/')
            uri.append("/");
        uri.append(master->workingDir);
    }

    if (uri[uri.length() - 1] != '/')
        uri.append("/");

    if (port->ftp_track_dirs && file) {
        static const CharacterSet Slash("/", "/");
        Parser::Tokenizer tok(*file);
        tok.skipAll(Slash);
        uri.append(tok.remaining());
    }
}