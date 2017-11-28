void
esiWhen::evaluate()
{
    if (!unevaluatedExpression)
        return;

    assert (varState);

    varState->feedData(unevaluatedExpression, strlen (unevaluatedExpression));

    char const *expression = varState->extractChar ();

    setTestResult(ESIExpression::Evaluate (expression));

    safe_free (expression);
}