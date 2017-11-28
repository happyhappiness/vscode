void
Adaptation::Ecap::XactionRep::doResume()
{
    Must(theMaster);
    theMaster->resume();
}