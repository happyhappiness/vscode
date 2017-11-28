bool
ACLHasComponentData::match(ACLChecklist *checklist)
{
    for (const auto method: componentMethods)
        if (method && (checklist->*method)())
            return true;
    return false;
}