SBufList
ACLIntRange::dump() const
{
    SBufList sl;
    CbDataListIterator<RangeType> iter(ranges);

    while (!iter.end()) {
        SBuf sb;
        const RangeType & element = iter.next();

        if (element.size() == 1)
            sb.Printf("%d", element.start);
        else
            sb.Printf("%d-%d", element.start, element.end-1);

        sl.push_back(sb);
    }

    return sl;
}