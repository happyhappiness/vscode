{
	if ((unsigned int)(options->check) > LZMA_CHECK_ID_MAX)
		return true;

	out[0] = 0x00;
	out[1] = options->check;

	return false;
}