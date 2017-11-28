void Adaptation::Icap::Options::cfgMethod(ICAP::Method m)
{
    Must(m != ICAP::methodNone);
    methods += m;
}