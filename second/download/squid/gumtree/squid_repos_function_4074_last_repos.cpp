int
ACLTimeStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *)
{
    return data->match(squid_curtime);
}