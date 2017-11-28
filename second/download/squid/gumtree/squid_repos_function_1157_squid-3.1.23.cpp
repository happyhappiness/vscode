static void
free_access_log(customlog ** definitions)
{
    while (*definitions) {
        customlog *log = *definitions;
        *definitions = log->next;

        log->logFormat = NULL;
        log->type = CLF_UNKNOWN;

        if (log->aclList)
            aclDestroyAclList(&log->aclList);

        safe_free(log->filename);

        xfree(log);
    }
}