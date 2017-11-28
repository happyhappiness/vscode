std::ostream &
operator <<(std::ostream &os, const Helper::Reply &r)
{
    os << "{result=";
    switch (r.result) {
    case Helper::Okay:
        os << "OK";
        break;
    case Helper::Error:
        os << "ERR";
        break;
    case Helper::BrokenHelper:
        os << "BH";
        break;
    case Helper::TT:
        os << "TT";
        break;
    case Helper::Unknown:
        os << "Unknown";
        break;
    }

    // dump the helper key=pair "notes" list
    if (!r.notes.empty()) {
        os << ", notes={";
        os << r.notes.toString("; ");
        os << "}";
    }

    if (r.other().hasContent())
        os << ", other: \"" << r.other().content() << '\"';

    os << '}';

    return os;
}