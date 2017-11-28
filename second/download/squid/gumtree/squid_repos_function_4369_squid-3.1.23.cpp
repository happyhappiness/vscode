void
aclDestroyRegexList(relist * data)
{
    relist *next = NULL;

    for (; data; data = next) {
        next = data->next;
        regfree(&data->regex);
        safe_free(data->pattern);
        memFree(data, MEM_RELIST);
    }
}