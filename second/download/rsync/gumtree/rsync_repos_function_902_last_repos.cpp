void poptSetExecPath(poptContext con, const char * path, int allowAbsolute)
{
    con->execPath = _free(con->execPath);
    con->execPath = xstrdup(path);
    con->execAbsolute = allowAbsolute;
    /*@-nullstate@*/ /* LCL: con->execPath not NULL */
    return;
    /*@=nullstate@*/
}