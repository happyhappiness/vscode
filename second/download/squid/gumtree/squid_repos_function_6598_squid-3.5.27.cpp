Trie *
ESICustomParser::GetTrie()
{
    if (SearchTrie)
        return SearchTrie;

    SearchTrie = new Trie(new TrieCaseless);

    static const ESITAG_t ESITAG_value = ESITAG;

    assert (SearchTrie->add
            ("<esi:",5,(void *)&ESITAG_value));

    static const ESITAG_t ESIENDTAG_value = ESIENDTAG;

    assert (SearchTrie->add
            ("</esi:",6,(void *)&ESIENDTAG_value));

    static const ESITAG_t ESICOMMENT_value = ESICOMMENT;

    assert (SearchTrie->add
            ("<!--",4,(void *)&ESICOMMENT_value));

    return SearchTrie;
}