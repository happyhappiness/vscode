const char *
mimeGetIconURL(const char *fn)
{
    SBuf icon(mimeGetIcon(fn));

    if (icon.isEmpty())
        return null_string;

    if (Config.icons.use_short_names) {
        static SBuf mb;
        mb.clear();
        mb.append("/squid-internal-static/icons/");
        mb.append(icon);
        return mb.c_str();
    } else {
        return internalLocalUri("/squid-internal-static/icons/", icon);
    }
}