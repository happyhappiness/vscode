void strarray_free (char **array, size_t array_len) /* {{{ */
{
	for (size_t i = 0; i < array_len; i++)
		sfree (array[i]);
	sfree (array);
}