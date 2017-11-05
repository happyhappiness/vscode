static int char_buffer_read(char_buffer_t *buffer, char *in, int inl)
{
    if (!buffer->length) {
        return 0;
    }

    if (buffer->length > inl) {
        /* we have have enough to fill the caller's buffer */
        memmove(in, buffer->value, inl);
        buffer->value += inl;
        buffer->length -= inl;
    }
    else {
        /* swallow remainder of the buffer */
        memmove(in, buffer->value, buffer->length);
        inl = buffer->length;
        buffer->value = NULL;
        buffer->length = 0;
    }

    return inl;
}