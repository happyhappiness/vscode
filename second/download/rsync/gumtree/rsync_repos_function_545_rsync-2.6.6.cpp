void poptSetExecPath(poptContext con, const char * path, int allowAbsolute)
{
    con->execPath = _free(con->execPath);
    con->execPath = xstrdup(path);
    con->execAbsolute = allowAbsolute;
    /*@-nullstate@*/ /* LCL: con->execPath can be NULL? */
    return;
    /*@=nullstate@*/
}