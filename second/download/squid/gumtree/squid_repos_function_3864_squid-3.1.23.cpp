void
Adaptation::Ecap::XactionRep::adaptationDelayed(const libecap::Delay &d)
{
    debugs(93,3, HERE << "adapter needs time: " <<
           d.state << '/' << d.progress);
    // XXX: set timeout?
}