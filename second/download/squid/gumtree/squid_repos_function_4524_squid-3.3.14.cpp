int
ACLPeerNameStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (checklist->dst_peer != NULL && checklist->dst_peer->name != NULL)
        return data->match(checklist->dst_peer->name);
    return 0;
}