void replace_special (char *buffer, size_t buffer_size)
{
	for (size_t i = 0; i < buffer_size; i++)
	{
		if (buffer[i] == 0)
			return;
		if ((!isalnum ((int) buffer[i])) && (buffer[i] != '-'))
			buffer[i] = '_';
	}
}