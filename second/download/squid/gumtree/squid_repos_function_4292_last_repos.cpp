int
ACLHierCodeStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (checklist->request->hier.code);
}