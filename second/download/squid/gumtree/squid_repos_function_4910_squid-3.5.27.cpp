ACLData<char const *> *
ACLAdaptationServiceData::clone() const
{
    return new ACLAdaptationServiceData(*this);
}