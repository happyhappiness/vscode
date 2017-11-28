int
ACLMyIP::match(ACLChecklist *checklist)
{
    return ACLIP::match (Filled(checklist)->my_addr);
}