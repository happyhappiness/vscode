CharacterSet
CharacterSet::complement(const char *label) const
{
    CharacterSet result((label ? label : "complement_of_some_other_set"), "");
    // negate each of our elements and add them to the result storage
    std::transform(chars_.begin(), chars_.end(), result.chars_.begin(),
                   std::logical_not<Storage::value_type>());
    return result;
}