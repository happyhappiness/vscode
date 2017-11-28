int
strListIsSubstr(const String * list, const char *s, char del)
{
    assert(list && del);
    return (list->find(s) != String::npos);

    /** \note
     * Note: the original code with a loop is broken because it uses strstr()
     * instead of strnstr(). If 's' contains a 'del', strListIsSubstr() may
     * return true when it should not. If 's' does not contain a 'del', the
     * implementaion is equavalent to strstr()! Thus, we replace the loop with
     * strstr() above until strnstr() is available.
     */
}