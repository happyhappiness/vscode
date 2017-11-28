bool
Helper::Reply::accumulate(const char *buf, size_t len)
{
    if (other_.isNull())
        other_.init(4*1024, 1*1024*1024);

    if (other_.potentialSpaceSize() < static_cast<mb_size_t>(len))
        return false; // no space left

    other_.append(buf, len);
    return true;
}