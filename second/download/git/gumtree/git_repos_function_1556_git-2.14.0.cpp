static void diff_words_append(char *line, unsigned long len,
		struct diff_words_buffer *buffer)
{
	ALLOC_GROW(buffer->text.ptr, buffer->text.size + len, buffer->alloc);
	line++;
	len--;
	memcpy(buffer->text.ptr + buffer->text.size, line, len);
	buffer->text.size += len;
	buffer->text.ptr[buffer->text.size] = '\0';
}