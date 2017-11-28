Adaptation::Icap::History& Adaptation::Icap::History::operator=(const History& ih)
{
    if (this != &ih)
        assign(ih);
    return *this;
}