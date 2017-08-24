{
	// Reserved bits must be unset.
	if (in[0] != 0x00 || (in[1] & 0xF0))
		return true;

	options->version = 0;
	options->check = in[1] & 0x0F;

	return false;
}