static void prep_base85(void)
{
	int i;
	if (de85['Z'])
		return;
	for (i = 0; i < ARRAY_SIZE(en85); i++) {
		int ch = en85[i];
		de85[ch] = i + 1;
	}
}