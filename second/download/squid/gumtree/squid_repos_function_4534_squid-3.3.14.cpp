inline
ACLFilledChecklist *Filled(ACLChecklist *checklist)
{
    // this should always be safe because ACLChecklist is an abstract class
    // and ACLFilledChecklist is its only [concrete] child
    return dynamic_cast<ACLFilledChecklist*>(checklist);
}