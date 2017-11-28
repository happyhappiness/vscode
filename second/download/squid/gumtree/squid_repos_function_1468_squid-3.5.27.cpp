void
SBuf::toLower()
{
    debugs(24, 8, "\"" << *this << "\"");
    for (size_type j = 0; j < length(); ++j) {
        const int c = (*this)[j];
        if (isupper(c))
            setAt(j, tolower(c));
    }
    debugs(24, 8, "result: \"" << *this << "\"");
    ++stats.caseChange;
}