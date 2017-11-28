void HttpReply::removeStaleWarnings()
{
    String warning;
    if (header.getList(Http::HdrType::WARNING, &warning)) {
        const String newWarning = removeStaleWarningValues(warning);
        if (warning.size() && warning.size() == newWarning.size())
            return; // some warnings are there and none changed
        header.delById(Http::HdrType::WARNING);
        if (newWarning.size()) { // some warnings left
            HttpHeaderEntry *const e =
                new HttpHeaderEntry(Http::HdrType::WARNING, NULL, newWarning.termedBuf());
            header.addEntry(e);
        }
    }
}