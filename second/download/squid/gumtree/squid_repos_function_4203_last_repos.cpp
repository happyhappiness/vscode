void
Acl::OptionExtractor::extractShort()
{
    debugs(28, 8, "from " << prefix_ << " at " << letterPos_ << " value: " << sawValue_);
    name.assign(prefix_.rawContent(), 1); // leading - or +
    name.append(prefix_.at(letterPos_++));
    if (letterPos_ >= prefix_.length()) { // got last flag in the sequence
        hasValue = sawValue_;
        prefix_.clear();
    } else {
        hasValue = false;
    }
}