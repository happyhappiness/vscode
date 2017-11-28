void
Ftp::Gateway::checkUrlpath()
{
    static SBuf str_type_eq("type=");
    auto t = request->url.path().rfind(';');

    if (t != SBuf::npos) {
        auto filenameEnd = t-1;
        if (request->url.path().substr(++t).cmp(str_type_eq, str_type_eq.length()) == 0) {
            t += str_type_eq.length();
            typecode = (char)xtoupper(request->url.path()[t]);
            request->url.path(request->url.path().substr(0,filenameEnd));
        }
    }

    int l = request->url.path().length();
    /* check for null path */

    if (!l) {
        flags.isdir = 1;
        flags.root_dir = 1;
        flags.need_base_href = 1;   /* Work around broken browsers */
    } else if (!request->url.path().cmp("/%2f/")) {
        /* UNIX root directory */
        flags.isdir = 1;
        flags.root_dir = 1;
    } else if ((l >= 1) && (request->url.path()[l-1] == '/')) {
        /* Directory URL, ending in / */
        flags.isdir = 1;

        if (l == 1)
            flags.root_dir = 1;
    } else {
        flags.dir_slash = 1;
    }
}