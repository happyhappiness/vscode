void
DescriptorSet::print(std::ostream &os) const
{
    // \todo add "name" if the set is used for more than just half-closed FDs
    os << size_ << " FDs";
}