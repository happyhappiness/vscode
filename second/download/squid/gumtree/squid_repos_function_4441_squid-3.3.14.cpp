int
ACLSslErrorStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    return data->match (checklist->sslErrors);
}