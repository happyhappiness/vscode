void
Adaptation::Ecap::XactionRep::vbDiscard()
{
    Must(makingVb == opUndecided);
    // if adapter does not need vb, we do not need to send it
    sinkVb("vbDiscard");
    Must(makingVb == opNever);
}