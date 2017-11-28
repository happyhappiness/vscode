static const CharacterSet &
UriValidCharacters()
{
    /* RFC 3986 section 2:
     * "
     *   A URI is composed from a limited set of characters consisting of
     *   digits, letters, and a few graphic symbols.
     * "
     */
    static const CharacterSet UriChars =
        CharacterSet("URI-Chars","") +
        // RFC 3986 section 2.2 - reserved characters
        CharacterSet("gen-delims", ":/?#[]@") +
        CharacterSet("sub-delims", "!$&'()*+,;=") +
        // RFC 3986 section 2.3 - unreserved characters
        CharacterSet::ALPHA +
        CharacterSet::DIGIT +
        CharacterSet("unreserved", "-._~") +
        // RFC 3986 section 2.1 - percent encoding "%" HEXDIG
        CharacterSet("pct-encoded", "%") +
        CharacterSet::HEXDIG;

    return UriChars;
}