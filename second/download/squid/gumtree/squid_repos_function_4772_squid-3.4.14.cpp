wordlist*
Acl::InnerNode::dump() const
{
    wordlist *values = NULL;
    for (Nodes::const_iterator i = nodes.begin(); i != nodes.end(); ++i)
        wordlistAdd(&values, (*i)->name);
    return values;
}