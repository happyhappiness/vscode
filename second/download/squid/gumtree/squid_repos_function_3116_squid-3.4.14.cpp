const char *
mimeGetIconURL(const char *fn)
{
    char const *icon = mimeGetIcon(fn);

    if (icon == NULL)
        return null_string;

    if (Config.icons.use_short_names) {
        static MemBuf mb;
        mb.reset();
        mb.Printf("/squid-internal-static/icons/%s", icon);
        return mb.content();
    } else {
        return internalLocalUri("/squid-internal-static/icons/", icon);
    }
}