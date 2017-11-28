void
FtpStateData::checkUrlpath()
{
    int l;
    size_t t;

    if (str_type_eq.undefined()) //hack. String doesn't support global-static
        str_type_eq="type=";

    if ((t = request->urlpath.rfind(';')) != String::npos) {
        if (request->urlpath.substr(t+1,t+1+str_type_eq.size())==str_type_eq) {
            typecode = (char)xtoupper(request->urlpath[t+str_type_eq.size()+1]);
            request->urlpath.cut(t);
        }
    }

    l = request->urlpath.size();
    /* check for null path */

    if (!l) {
        flags.isdir = 1;
        flags.root_dir = 1;
        flags.need_base_href = 1;	/* Work around broken browsers */
    } else if (!request->urlpath.cmp("/%2f/")) {
        /* UNIX root directory */
        flags.isdir = 1;
        flags.root_dir = 1;
    } else if ((l >= 1) && (request->urlpath[l - 1] == '/')) {
        /* Directory URL, ending in / */
        flags.isdir = 1;

        if (l == 1)
            flags.root_dir = 1;
    } else {
        flags.dir_slash = 1;
    }
}