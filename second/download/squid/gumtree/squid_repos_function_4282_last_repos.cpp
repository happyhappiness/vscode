int
ACLLocalIP::match(ACLChecklist *checklist)
{
    return ACLIP::match (Filled(checklist)->my_addr);
}