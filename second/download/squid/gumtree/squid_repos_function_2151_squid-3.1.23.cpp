void
ServerStateData::adaptationAclCheckDoneWrapper(Adaptation::ServiceGroupPointer group, void *data)
{
    ServerStateData *state = (ServerStateData *)data;
    state->adaptationAclCheckDone(group);
}