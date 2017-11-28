void
ESIVarState::doIt ()
{
    char *string = input->listToChar();
    ESISegmentFreeList (input);
    ESIVariableProcessor theProcessor(string, output, variables, this);
    theProcessor.doIt();
    safe_free(string);
}