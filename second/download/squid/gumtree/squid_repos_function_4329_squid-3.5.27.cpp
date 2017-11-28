const char *
Ftp::UnescapeDoubleQuoted(const char *quotedPath)
{
    static MemBuf path;
    path.reset();
    const char *s = quotedPath;
    if (*s == '"') {
        ++s;
        bool parseDone = false;
        while (!parseDone) {
            if (const char *e = strchr(s, '"')) {
                path.append(s, e - s);
                s = e + 1;
                if (*s == '"') {
                    path.append(s, 1);
                    ++s;
                } else
                    parseDone = true;
            } else { //parse error
                parseDone = true;
                path.reset();
            }
        }
    }
    return path.content();
}