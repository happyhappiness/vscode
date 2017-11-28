void
MimeIcon::_free()
{
    safe_free (icon);
    safe_free (url);
}