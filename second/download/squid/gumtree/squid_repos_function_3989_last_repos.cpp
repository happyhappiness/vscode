int
ACLSquidErrorStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->requestErrorType != ERR_MAX)
        return data->match(checklist->requestErrorType);
    else if (checklist->request)
        return data->match(checklist->request->errType);
    return 0;
}