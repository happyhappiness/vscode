std::ostream &
operator <<(std::ostream &os, const HelperReply &r)
{
    os << "{result=";
    switch (r.result) {
    case HelperReply::Okay:
        os << "OK";
        break;
    case HelperReply::Error:
        os << "ERR";
        break;
    case HelperReply::BrokenHelper:
        os << "BH";
        break;
    case HelperReply::TT:
        os << "TT";
        break;
    case HelperReply::Unknown:
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