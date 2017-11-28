bool
ACLIntRange::match(int i)
{
    RangeType const toFind(i, i+1);
    for (std::list<RangeType>::const_iterator iter = ranges.begin(); iter != ranges.end(); ++iter) {
        const RangeType & element = *iter;
        RangeType result = element.intersection(toFind);

        if (result.size())
            return true;
    }

    return false;
}