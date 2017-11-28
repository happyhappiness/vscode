static void
free_externalAclState(void *data)
{
    externalAclState *state = static_cast<externalAclState *>(data);
    safe_free(state->key);
    cbdataReferenceDone(state->callback_data);
    cbdataReferenceDone(state->def);
}