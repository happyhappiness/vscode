
    xfree(name);
    return m;
}

MimeIcon::MimeIcon(const char *aName) :
    url_(nullptr)
{
    setName(aName);
}

MimeIcon::~MimeIcon()
{
    xfree(url_);
}

void
MimeIcon::setName(char const *aString)
{
    xfree(url_);
    icon_ = aString;
    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
}

SBuf
MimeIcon::getName() const
{
    return icon_;
}

const SBuf
mimeGetIcon(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);

    if (!m || !m->theIcon.getName().cmp(dash_str))
        return SBuf();

    return m->theIcon.getName();
}

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

const char *
