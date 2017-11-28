int
ACLSourceASNStrategy::match (ACLData<Ip::Address> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    return data->match(checklist->src_addr);
}