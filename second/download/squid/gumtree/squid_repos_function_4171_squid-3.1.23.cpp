ACLData<time_t> *
ACLTimeData::clone() const
{
    return new ACLTimeData(*this);
}