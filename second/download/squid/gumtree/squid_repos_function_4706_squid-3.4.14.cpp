int
ACLMethodStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match (checklist->request->method);
}