std::ostream &
Adaptation::ServicePlan::print(std::ostream &os) const
{
    if (!group)
        return os << "[nil]";

    return os << group->id << '[' << pos << ".." << group->services.size() <<
           (atEof ? ".]" : "]");
}