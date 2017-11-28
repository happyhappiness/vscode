void
Adaptation::Ecap::XactionRep::vbStopMaking()
{
    Must(makingVb == opOn);
    // if adapter does not need vb, we do not need to receive it
    sinkVb("vbStopMaking");
    Must(makingVb == opComplete);
}