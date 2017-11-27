static void submit_derive (const char *dev, const char *type, const char *ti1,
				const char *ti2, derive_t val)
{
	value_t item;
	item.derive = val;
	submit (dev, type, ti1, ti2, &item, 1);
}