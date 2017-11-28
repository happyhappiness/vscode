char *
xstrcat( char *src, const char *dst)
{
    if (dst) {
        if (strlen(src)+strlen(dst)+1>MAX_PAC_GROUP_SIZE)
            return NULL;
        else
            return strcat(src,dst);
    } else
        return src;
}