void
MimeIcon::setName (char const *aString)
{
    safe_free (icon);
    safe_free (url);
    icon = xstrdup (aString);
    url = xstrdup (internalLocalUri("/squid-internal-static/icons/", icon));
}