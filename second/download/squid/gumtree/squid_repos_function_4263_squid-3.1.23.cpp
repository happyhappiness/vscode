int
ACLTagStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->request != NULL)
        return data->match (checklist->request->tag.termedBuf());
    return 0;
}