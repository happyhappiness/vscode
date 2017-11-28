void
Adaptation::Ecap::XactionRep::master(const AdapterXaction &x)
{
    Must(!theMaster);
    Must(x);
    theMaster = x;
}