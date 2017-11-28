size_t
ESISegment::listLength() const
{
    size_t result = 0;
    ESISegment const* temp = this;

    while (temp) {
        result += temp->len;
        temp = temp->next.getRaw();
    }

    return result;
}