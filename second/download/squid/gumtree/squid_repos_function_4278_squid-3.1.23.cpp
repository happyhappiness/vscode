int
ACLMyPortStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (checklist->my_addr.GetPort());
}