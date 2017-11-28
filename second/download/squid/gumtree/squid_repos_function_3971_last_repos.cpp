int
Acl::TransactionInitiator::match(ACLChecklist *checklist)
{
    ACLFilledChecklist *filled = Filled((ACLChecklist*)checklist);
    assert(filled->request);
    assert(filled->request->masterXaction);
    const XactionInitiator requestInitiator = filled->request->masterXaction->initiator;
    return requestInitiator.in(initiators_) ? 1 : 0;
}