int
ACLSourceASNStrategy::match (ACLData<IpAddress> * &data, ACLFilledChecklist *checklist)
{
    return data->match(checklist->src_addr);
}