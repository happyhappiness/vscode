void
ESIVarState::addVariable(char const *name, size_t len, Variable *aVariable)
{
    String temp;
    temp.limitInit (name, len);
    removeVariable (temp);
    variables.add(name, len, aVariable);
    variablesForCleanup.push_back(aVariable);
}