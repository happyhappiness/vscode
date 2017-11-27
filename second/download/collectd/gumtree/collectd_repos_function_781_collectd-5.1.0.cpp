static int
lv_init (void)
{
    if (virInitialize () != 0)
        return -1;

	return 0;
}