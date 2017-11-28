void
Adaptation::Ecap::XactionRep::vbDiscard()
{
    Must(proxyingVb == opUndecided);
    // if adapter does not need vb, we do not need to send it
    dropVirgin("vbDiscard");
    Must(proxyingVb == opNever);
}