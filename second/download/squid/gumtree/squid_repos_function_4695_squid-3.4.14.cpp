static void
aclDestroyRegexList(RegexList * data)
{
    RegexList *next = NULL;

    for (; data; data = next) {
        next = data->next;
        regfree(&data->regex);
        safe_free(data->pattern);
        memFree(data, MEM_RELIST);
    }
}