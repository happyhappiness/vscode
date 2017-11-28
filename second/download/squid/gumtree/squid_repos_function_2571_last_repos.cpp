void
MimeIcon::setName(char const *aString)
{
    xfree(url_);
    icon_ = aString;
    url_ = xstrdup(internalLocalUri("/squid-internal-static/icons/", icon_));
}