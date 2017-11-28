ESIVarState::Variable *
ESIVarState::GetVar(char const *symbol, int len)
{
    assert (symbol);

    void *result = variables.find (symbol, len);

    if (result)
        return static_cast<Variable *>(result);

    return defaultVariable;
}