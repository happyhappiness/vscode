void
Adaptation::ServiceGroup::checkUniqueness(const Pos checkedPos) const
{
    ServicePointer checkedService = at(checkedPos);
    if (!checkedService) // should not happen but be robust
        return;

    for (Pos p = checkedPos + 1; has(p); ++p) {
        ServicePointer s = at(p);
        if (s != NULL && s->cfg().key == checkedService->cfg().key)
            finalizeMsg("duplicate service name", s->cfg().key, false);
        else if (s != NULL && s->cfg().uri == checkedService->cfg().uri)
            finalizeMsg("duplicate service URI", s->cfg().uri, false);
    }
}