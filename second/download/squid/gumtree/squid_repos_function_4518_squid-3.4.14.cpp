int
ACLHTTPReqHeaderStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match (&checklist->request->header);
}