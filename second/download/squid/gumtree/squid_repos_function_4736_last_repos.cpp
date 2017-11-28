const char*
SBuf::c_str()
{
    ++stats.rawAccess;
    /* null-terminate the current buffer, by hand-appending a \0 at its tail but
     * without increasing its length. May COW, the side-effect is to guarantee that
     * the MemBlob's tail is availabe for us to use */
    *rawSpace(1) = '\0';
    ++store_->size;
    ++stats.setChar;
    ++stats.nulTerminate;
    return buf();
}