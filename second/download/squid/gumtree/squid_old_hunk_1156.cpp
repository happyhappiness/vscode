
    xfree(name);
    return m;
}

MimeIcon::MimeIcon(const char *aName) :
    icon_(xstrdup(aName))
{
    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
}

MimeIcon::~MimeIcon()
{
    xfree(icon_);
    xfree(url_);
}

void
MimeIcon::setName(char const *aString)
{
    xfree(icon_);
    xfree(url_);
    icon_ = xstrdup(aString);
    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
}

char const *
MimeIcon::getName() const
{
    return icon_;
}

char const *
mimeGetIcon(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);

    if (m == NULL)
        return NULL;

    if (!strcmp(m->theIcon.getName(), dash_str))
        return NULL;

    return m->theIcon.getName();
}

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

const char *
