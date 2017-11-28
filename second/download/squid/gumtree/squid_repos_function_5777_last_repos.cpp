char *
pstrcpy( char *src, const char *dst)
{
    if (dst) {
        if (strlen(dst)>MAX_PAC_GROUP_SIZE)
            return NULL;
        else
            return strcpy(src,dst);
    } else
        return src;
}