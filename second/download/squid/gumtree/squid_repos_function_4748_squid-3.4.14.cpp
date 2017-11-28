int
ACLNoteStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    if (checklist->request != NULL)
        return data->match(checklist->request);

    return 0;
}