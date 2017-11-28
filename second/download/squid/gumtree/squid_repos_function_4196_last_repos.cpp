int
ACLAdaptationServiceStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    HttpRequest::Pointer request = checklist->request;
    if (request == NULL)
        return 0;
    Adaptation::History::Pointer ah = request->adaptHistory();
    if (ah == NULL)
        return 0;

    Adaptation::History::AdaptationServices::iterator it;
    for (it = ah->theAdaptationServices.begin(); it != ah->theAdaptationServices.end(); ++it) {
        if (data->match(it->c_str()))
            return 1;
    }

    return 0;
}