void
Adaptation::Ecap::XactionRep::adaptationAborted()
{
    tellQueryAborted(true); // should eCAP support retries?
    mustStop("adaptationAborted");
}