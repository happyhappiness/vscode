int
ACLHTTPRepHeaderStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match (&checklist->reply->header);
}