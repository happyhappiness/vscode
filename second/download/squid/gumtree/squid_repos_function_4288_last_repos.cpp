SBufList
ACLIntRange::dump() const
{
    SBufList sl;
    for (std::list<RangeType>::const_iterator iter = ranges.begin(); iter != ranges.end(); ++iter) {
        SBuf sb;
        const RangeType & element = *iter;

        if (element.size() == 1)
            sb.Printf("%d", element.start);
        else
            sb.Printf("%d-%d", element.start, element.end-1);

        sl.push_back(sb);
    }

    return sl;
}