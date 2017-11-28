void Adaptation::Icap::Xaction::dieOnConnectionFailure()
{
    debugs(93, 2, HERE << typeName <<
           " failed to connect to " << service().cfg().uri);
    theService->noteFailure();
    throw TexcHere("cannot connect to the ICAP service");
}