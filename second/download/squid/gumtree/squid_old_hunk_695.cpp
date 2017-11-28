    if (!ranges.empty())
        fatal("ACLIntRange::clone: attempt to clone used ACL");

    return new ACLIntRange (*this);
}

ACLIntRange::~ACLIntRange ()
{}

wordlist *
ACLIntRange::dump ()
{
    wordlist *W = NULL;
    char buf[32];
    CbDataListIterator<RangeType> iter(ranges);

    while (!iter.end()) {
        const RangeType & element = iter.next();

        if (element.size() == 1)
            snprintf(buf, sizeof(buf), "%d", element.start);
        else
            snprintf(buf, sizeof(buf), "%d-%d", element.start, element.end-1);

        wordlistAdd(&W, buf);
    }

    return W;
}

