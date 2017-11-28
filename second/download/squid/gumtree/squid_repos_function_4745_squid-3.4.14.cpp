bool
ACLIntRange::match(int i)
{
    RangeType const toFind (i, i+1);
    CbDataListIterator<RangeType> iter(ranges);

    while (!iter.end()) {
        const RangeType & element = iter.next();
        RangeType result = element.intersection (toFind);

        if (result.size())
            return true;
    }

    return false;
}