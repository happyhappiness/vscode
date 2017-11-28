bool Adaptation::Icap::ModXact::shouldAllow206in()
{
    return shouldAllow206any() && preview.enabled();
}