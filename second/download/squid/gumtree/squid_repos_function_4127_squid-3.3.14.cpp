void Adaptation::Icap::Xaction::dieOnConnectionFailure()
{
    debugs(93, 2, HERE << typeName <<
           " failed to connect to " << service().cfg().uri);
    service().noteConnectionFailed("failure");
    detailError(ERR_DETAIL_ICAP_XACT_START);
    throw TexcHere("cannot connect to the ICAP service");
}