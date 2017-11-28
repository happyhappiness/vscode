char *
SBuf::rawSpace(size_type minSpace)
{
    Must(length() <= maxSize - minSpace);
    debugs(24, 7, "reserving " << minSpace << " for " << id);
    ++stats.rawAccess;
    // we're not concerned about RefCounts here,
    // the store knows the last-used portion. If
    // it's available, we're effectively claiming ownership
    // of it. If it's not, we need to go away (realloc)
    if (store_->canAppend(off_+len_, minSpace)) {
        debugs(24, 7, id << " not growing");
        return bufEnd();
    }
    // TODO: we may try to memmove before realloc'ing in order to avoid
    //   one allocation operation, if we're the sole owners of a MemBlob.
    //   Maybe some heuristic on off_ and length()?
    cow(minSpace+length());
    return bufEnd();
}