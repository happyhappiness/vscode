void
httpHdrAdd(HttpHeader *heads, HttpRequest *request, const AccessLogEntryPointer &al, HeaderWithAclList &headersAdd)
{
    ACLFilledChecklist checklist(NULL, request, NULL);

    for (HeaderWithAclList::const_iterator hwa = headersAdd.begin(); hwa != headersAdd.end(); ++hwa) {
        if (!hwa->aclList || checklist.fastCheck(hwa->aclList) == ACCESS_ALLOWED) {
            const char *fieldValue = NULL;
            MemBuf mb;
            if (hwa->quoted) {
                if (al != NULL) {
                    mb.init();
                    hwa->valueFormat->assemble(mb, al, 0);
                    fieldValue = mb.content();
                }
            } else {
                fieldValue = hwa->fieldValue.c_str();
            }

            if (!fieldValue || fieldValue[0] == '\0')
                fieldValue = "-";

            HttpHeaderEntry *e = new HttpHeaderEntry(hwa->fieldId, hwa->fieldName.c_str(),
                    fieldValue);
            heads->addEntry(e);
        }
    }
}