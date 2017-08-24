{
	size_t i;
	for (i = 0; i < ARRAY_SIZE(decoders); ++i)
		if (decoders[i].id == id)
			return decoders + i;

	return NULL;
}