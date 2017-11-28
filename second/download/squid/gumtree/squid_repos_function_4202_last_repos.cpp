void
Acl::OptionExtractor::extractWhole()
{
    debugs(28, 8, "from " << prefix_ << " value: " << sawValue_);
    hasValue = sawValue_;
    name = prefix_;
    prefix_.clear();
}