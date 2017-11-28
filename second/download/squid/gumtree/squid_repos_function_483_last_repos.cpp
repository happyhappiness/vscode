bool HttpReply::inheritProperties(const HttpMsg *aMsg)
{
    const HttpReply *aRep = dynamic_cast<const HttpReply*>(aMsg);
    if (!aRep)
        return false;
    keep_alive = aRep->keep_alive;
    sources = aRep->sources;
    return true;
}