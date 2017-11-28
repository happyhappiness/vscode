esiProcessResult_t
esiChoose::process (int dovars)
{
    /* process as much of the list as we can, stopping only on
     * faliures
     */
    /* We MUST have a when clause */
    NULLUnChosen();

    if (!elements.size()) {
        parent->fail(this);

        if (otherwise.getRaw())
            otherwise->finish();

        otherwise = NULL;

        parent = NULL;

        return ESI_PROCESS_FAILED;
    }

    if (chosenelement >= 0) {
        return elements[chosenelement]->process(dovars);
    } else if (otherwise.getRaw())
        return otherwise->process(dovars);
    else
        return ESI_PROCESS_COMPLETE;
}