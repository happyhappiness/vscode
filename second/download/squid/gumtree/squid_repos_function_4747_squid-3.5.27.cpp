int
ACLTimeStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match (squid_curtime);
}