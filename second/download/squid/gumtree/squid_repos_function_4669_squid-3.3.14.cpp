int
ACLSourceASNStrategy::match (ACLData<Ip::Address> * &data, ACLFilledChecklist *checklist)
{
    return data->match(checklist->src_addr);
}