void
Adaptation::Ecap::XactionRep::terminateMaster()
{
    if (theMaster) {
        AdapterXaction x = theMaster;
        theMaster.reset();
        x->stop();
    }
}