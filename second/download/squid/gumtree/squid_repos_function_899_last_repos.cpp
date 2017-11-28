static void free_HeaderWithAclList(HeaderWithAclList **header)
{
    if (!(*header))
        return;

    for (HeaderWithAclList::iterator hwa = (*header)->begin(); hwa != (*header)->end(); ++hwa) {
        if (hwa->aclList)
            aclDestroyAclList(&hwa->aclList);

        if (hwa->valueFormat) {
            delete hwa->valueFormat;
            hwa->valueFormat = NULL;
        }
    }
    delete *header;
    *header = NULL;
}