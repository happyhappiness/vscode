void Adaptation::History::recordMeta(const HttpHeader *lm)
{
    lastMeta.clean();
    lastMeta.update(lm, NULL);

    allMeta.update(lm, NULL);
    allMeta.compact();
}