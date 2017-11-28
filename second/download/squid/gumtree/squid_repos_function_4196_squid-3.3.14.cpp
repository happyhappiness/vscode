void Adaptation::Icap::ServiceRep::detach()
{
    debugs(93,3, HERE << "detaching ICAP service: " << cfg().uri <<
           ' ' << status());
    isDetached = true;
}