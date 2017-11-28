int
ACLTimeStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (squid_curtime);
}