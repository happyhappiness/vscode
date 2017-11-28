void
ESIVariableExpression::eval (ESIVarState &state, char const *subref, char const *defaultOnEmpty) const
{
    /* XXX: Implement evaluation of the expression */
    ESISegment::ListAppend (state.getOutput(), expression.rawBuf(), expression.size());
}