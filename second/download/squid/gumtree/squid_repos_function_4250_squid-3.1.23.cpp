int
ACLSourceIP::match(ACLChecklist *checklist)
{
    return ACLIP::match(Filled(checklist)->src_addr);
}