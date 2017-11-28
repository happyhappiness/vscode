void
ESISegment::listAppend (char const *s, size_t length)
{
    assert (next.getRaw() == NULL);
    ESISegment::Pointer output = this;
    /* copy the string to output */
    size_t pos=0;

    while (pos < length) {
        if (output->space() == 0) {
            assert (output->next.getRaw() == NULL);
            output->next = new ESISegment;
            output = output->next;
        }

        pos += output->append(s + pos, length - pos);
    }
}