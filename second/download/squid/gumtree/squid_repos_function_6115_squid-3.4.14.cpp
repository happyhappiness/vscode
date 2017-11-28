void
ESIAssign::evaluateVariable()
{
    if (variable.getRaw())
        variable->process (false);

    variable = NULL;

    if (unevaluatedVariable.size()) {
        varState->feedData(unevaluatedVariable.rawBuf(), unevaluatedVariable.size());
        char const *result = varState->extractChar ();

        /* Consider activating this, when we want to evaluate variables to a
         * value
         */
        // setTestResult(ESIExpression::Evaluate (expression));

        value = new ESIVariableExpression (result);

        safe_free (result);
    }
}