struct userdiff_driver *userdiff_get_textconv(struct userdiff_driver *driver)
{
	if (!driver->textconv)
		return NULL;

	if (driver->textconv_want_cache && !driver->textconv_cache) {
		struct notes_cache *c = xmalloc(sizeof(*c));
		struct strbuf name = STRBUF_INIT;

		strbuf_addf(&name, "textconv/%s", driver->name);
		notes_cache_init(c, name.buf, driver->textconv);
		driver->textconv_cache = c;
	}

	return driver;
}