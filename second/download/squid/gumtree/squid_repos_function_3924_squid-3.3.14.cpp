Adaptation::Ecap::BodyRep::BodySize
Adaptation::Ecap::BodyRep::bodySize() const
{
    return !theBody ? BodySize() : BodySize(theBody->bodySize());
}