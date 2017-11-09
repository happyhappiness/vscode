static int char_buffer_write(char_buffer_t *buffer, char *in, int inl)
{
    buffer->value = in;
    buffer->length = inl;
    return inl;
}