int
ACLPeerNameStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    if (!checklist->dst_peer_name.isEmpty())
        return data->match(checklist->dst_peer_name.c_str());
    return 0;
}