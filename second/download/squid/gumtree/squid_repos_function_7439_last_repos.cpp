bool
Security::Extension::supported() const
{
    static const Extensions supportedExtensions = SupportedExtensions();
    return supportedExtensions.find(type) != supportedExtensions.end();
}