int _crypt_output_magic(const char *setting, char *output, int size)
{
	if (size < 3)
		return -1;

	output[0] = '*';
	output[1] = '0';
	output[2] = '\0';

	if (setting[0] == '*' && setting[1] == '0')
		output[1] = '1';

	return 0;
}