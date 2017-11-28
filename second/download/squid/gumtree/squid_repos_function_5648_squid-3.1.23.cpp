char *
strerror(int ern)
{
    return sys_errlist[ern];
}