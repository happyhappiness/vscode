const char *
LogTags::c_str() const
{
    static char buf[1024];
    *buf = 0;
    int pos = 0;

    // source tags
    if (oldType && oldType < LOG_TYPE_MAX)
        pos += snprintf(buf, sizeof(buf), "%s",Str_[oldType]);
    else
        pos += snprintf(buf, sizeof(buf), "NONE");

    if (err.ignored)
        pos += snprintf(buf+pos,sizeof(buf)-pos, "_IGNORED");

    // error tags
    if (err.timedout)
        pos += snprintf(buf+pos,sizeof(buf)-pos, "_TIMEDOUT");
    if (err.aborted)
        pos += snprintf(buf+pos,sizeof(buf)-pos, "_ABORTED");

    return buf;
}