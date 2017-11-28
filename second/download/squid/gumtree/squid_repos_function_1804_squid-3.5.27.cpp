void
strListAdd(String * str, const char *item, char del)
{
    assert(str && item);
    const String::size_type itemSize = strlen(item);
    if (str->size()) {
        char buf[3];
        buf[0] = del;
        buf[1] = ' ';
        buf[2] = '\0';
        Must(str->canGrowBy(2));
        str->append(buf, 2);
    }
    Must(str->canGrowBy(itemSize));
    str->append(item, itemSize);
}