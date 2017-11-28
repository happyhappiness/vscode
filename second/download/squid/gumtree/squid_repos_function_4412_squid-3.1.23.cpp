int
ACLHTTPRepHeaderStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (&checklist->reply->header);
}