Adaptation::Ecap::BodyRep::BodySize
Adaptation::Ecap::BodyRep::bodySize() const
{
    return (theBody != nullptr && theBody->bodySizeKnown()) ? BodySize(theBody->bodySize()) : BodySize();
}