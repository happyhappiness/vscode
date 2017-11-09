static const char *fallback_encoding(const char *name)
{
	/*
	 * Some platforms do not have the variously spelled variants of
	 * UTF-8, so let's fall back to trying the most official
	 * spelling. We do so only as a fallback in case the platform
	 * does understand the user's spelling, but not our official
	 * one.
	 */
	if (is_encoding_utf8(name))
		return "UTF-8";

	/*
	 * Even though latin-1 is still seen in e-mail
	 * headers, some platforms only install ISO-8859-1.
	 */
	if (!strcasecmp(name, "latin-1"))
		return "ISO-8859-1";

	return name;
}