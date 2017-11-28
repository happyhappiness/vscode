void
MimeIcon::setName(char const *aString)
{
    xfree(icon_);
    xfree(url_);
    icon_ = xstrdup(aString);
    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
}