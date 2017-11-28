int
ACLHTTPReqHeaderStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (&checklist->request->header);
}