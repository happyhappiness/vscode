void HttpReply::removeStaleWarnings()
{
    String warning;
    if (header.getList(HDR_WARNING, &warning)) {
        const String newWarning = removeStaleWarningValues(warning);
        if (warning.size() && warning.size() == newWarning.size())
            return; // some warnings are there and none changed
        header.delById(HDR_WARNING);
        if (newWarning.size()) { // some warnings left
            HttpHeaderEntry *const e =
                new HttpHeaderEntry(HDR_WARNING, NULL, newWarning.termedBuf());
            header.addEntry(e);
        }
    }
}