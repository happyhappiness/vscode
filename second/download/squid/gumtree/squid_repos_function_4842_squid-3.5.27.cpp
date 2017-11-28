bool ACLFlags::supported(const ACLFlag f) const
{
    if (f == ACL_F_REGEX_CASE)
        return true;
    return (supported_.find(f) != std::string::npos);
}