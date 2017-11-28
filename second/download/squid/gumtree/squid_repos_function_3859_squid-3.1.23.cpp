void
Adaptation::Ecap::XactionRep::vbMakeMore()
{
    Must(proxyingVb == opOn); // cannot make more if done proxying
    // we cannot guarantee more vb, but we can check that there is a chance
    Must(!theVirginRep.raw().body_pipe->exhausted());
}