void
Adaptation::Ecap::XactionRep::vbStopMaking()
{
    // if adapter does not need vb, we do not need to receive it
    if (proxyingVb == opOn)
        dropVirgin("vbStopMaking");
    Must(proxyingVb == opComplete);
}