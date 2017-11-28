char *
ESISegment::listToChar() const
{
    size_t length = listLength();
    char *rv = (char *)xmalloc (length + 1);
    assert (rv);
    rv [length] = '\0';

    ESISegment::Pointer temp = this;
    size_t pos = 0;

    while (temp.getRaw()) {
        xmemcpy (&rv[pos], temp->buf, temp->len);
        pos += temp->len;
        temp = temp->next;
    }

    return rv;
}