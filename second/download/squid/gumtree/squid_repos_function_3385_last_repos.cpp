libecap::Version
Adaptation::Ecap::FirstLineRep::version() const
{
    return libecap::Version(theMessage.http_ver.major,
                            theMessage.http_ver.minor);
}