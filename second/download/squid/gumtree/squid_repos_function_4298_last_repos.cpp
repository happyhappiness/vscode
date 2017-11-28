int
ACLHasComponentStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    ACLHasComponentData *cdata = dynamic_cast<ACLHasComponentData*>(data);
    assert(cdata);
    return cdata->match(checklist);
}