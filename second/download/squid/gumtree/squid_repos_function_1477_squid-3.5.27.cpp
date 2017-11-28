int
DelayUserCmp(DelayUserBucket::Pointer const &left, DelayUserBucket::Pointer const &right)
{
    /* Verify for re-currance of Bug 2127. either of these missing will crash strcasecmp() */
    assert(left->authUser->username() != NULL);
    assert(right->authUser->username() != NULL);

    /* for rate limiting, case insensitive */
    return strcasecmp(left->authUser->username(), right->authUser->username());
}