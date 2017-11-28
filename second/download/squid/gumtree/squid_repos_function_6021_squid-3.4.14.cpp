void
ESIContext::parserDefault (const char *s, int len)
{
    if (failed())
        return;

    /* handle any skipped data */
    addLiteral (s, len);
}