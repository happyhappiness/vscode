char *
AllocStrFromLSAStr(LSA_UNICODE_STRING LsaStr)
{
    size_t len;
    static char *target;

    len = LsaStr.Length / sizeof(WCHAR) + 1;

    /* allocate buffer for str + null termination */
    safe_free(target);
    target = (char *) xmalloc(len);
    if (target == NULL)
        return NULL;

    /* copy unicode buffer */
    WideCharToMultiByte(CP_ACP, 0, LsaStr.Buffer, LsaStr.Length, target, len, NULL, NULL);

    /* add null termination */
    target[len - 1] = '\0';
    return target;
}