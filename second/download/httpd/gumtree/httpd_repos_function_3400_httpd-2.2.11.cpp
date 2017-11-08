const char* expand_path(const char *relpath)
{
    char foo[PATH_MAX], *newpath;

    getcwd(foo, PATH_MAX-1);
    newpath = (char*)malloc(strlen(foo)+strlen(relpath)+2);
    strcat(newpath, foo);
    strcat(newpath, "/");
    strcat(newpath, relpath);
    return newpath;
}