char *
ConnStateData::In::addressToReadInto() const
{
    return buf + notYetUsed;
}