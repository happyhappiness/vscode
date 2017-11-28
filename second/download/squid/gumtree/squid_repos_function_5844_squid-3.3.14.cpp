void
Snmp::Var::setName(const Range<const oid*>& aName)
{
    clearName();
    if (aName.start != NULL && aName.size() != 0) {
        name_length = aName.size();
        name = static_cast<oid*>(xmalloc(name_length * sizeof(oid)));
        std::copy(aName.start, aName.end, name);
    }
}