wordlist*
Acl::NotNode::dump() const
{
    wordlist *text = NULL;
    wordlistAdd(&text, name);
    return text;
}