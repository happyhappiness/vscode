void
Adaptation::Ecap::XactionRep::master(const AdapterXaction &x)
{
    Must(!theMaster);
    Must(x != NULL);
    theMaster = x;
}