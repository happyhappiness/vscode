bool Adaptation::History::getXxRecord(String &name, String &value) const
{
    if (theXxName.size() <= 0)
        return false;

    name = theXxName;
    value = theXxValue;
    return true;
}