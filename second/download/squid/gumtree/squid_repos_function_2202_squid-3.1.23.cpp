void
strListAdd(String * str, const char *item, char del)
{
    assert(str && item);

    if (str->size()) {
        char buf[3];
        buf[0] = del;
        buf[1] = ' ';
        buf[2] = '\0';
        str->append(buf, 2);
    }

    str->append(item, strlen(item));
}