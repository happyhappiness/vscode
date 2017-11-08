void poptSetExecPath(poptContext con, const char * path, int allowAbsolute) {
    if (con->execPath) xfree(con->execPath);
    con->execPath = xstrdup(path);
    con->execAbsolute = allowAbsolute;
}