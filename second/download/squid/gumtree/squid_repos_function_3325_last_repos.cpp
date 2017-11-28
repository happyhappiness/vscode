void Adaptation::History::recordMeta(const HttpHeader *lm)
{
    lastMeta.clean();
    lastMeta.update(lm);

    allMeta.update(lm);
    allMeta.compact();
}