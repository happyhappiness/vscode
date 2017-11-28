void
ACLList::negated(bool isNegated)
{
    if (isNegated)
        op = 0;
    else
        op = 1;
}