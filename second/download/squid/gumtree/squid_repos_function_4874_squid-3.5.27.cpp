int
ACLProtocolStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match(checklist->request->url.getScheme());
}