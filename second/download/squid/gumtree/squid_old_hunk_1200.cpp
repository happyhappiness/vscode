     */
    tempBuffer.offset = mem_obj->endOffset() - (getReply() ? getReply()->hdr_sz : 0);
    write(tempBuffer);
}

void
storeAppendPrintf(StoreEntry * e, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);

    storeAppendVPrintf(e, fmt, args);
    va_end(args);
}

/* used be storeAppendPrintf and Packer */
void
storeAppendVPrintf(StoreEntry * e, const char *fmt, va_list vargs)
{
    LOCAL_ARRAY(char, buf, 4096);
    buf[0] = '\0';
    vsnprintf(buf, 4096, fmt, vargs);
    e->append(buf, strlen(buf));
}

struct _store_check_cachable_hist {

    struct {
        int non_get;
