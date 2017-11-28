void
ESIVariableProcessor::eval (ESIVarState::Variable *var, char const *subref, char const *foundDefault )
{
    assert (var);

    if (!foundDefault)
        foundDefault = "";

    var->eval (*varState, subref, foundDefault);
}