esiProcessResult_t
ESIAssign::process (int dovars)
{
    assert (varState);

    if (!value)
        evaluateVariable();

    if (!value)
        return ESI_PROCESS_COMPLETE;

    varState->addVariable (name.rawBuf(), name.size(), value);

    value = NULL;

    debugs(86, 5, "ESIAssign: Processed " << this);

    return ESI_PROCESS_COMPLETE;
}