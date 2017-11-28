void
HttpHdrRange::merge (Vector<HttpHdrRangeSpec *> &basis)
{
    /* reset old array */
    specs.clean();
    /* merge specs:
     * take one spec from "goods" and merge it with specs from
     * "specs" (if any) until there is no overlap */
    iterator i = basis.begin();

    while (i != basis.end()) {
        if (specs.size() && (*i)->mergeWith(specs.back())) {
            /* merged with current so get rid of the prev one */
            delete specs.pop_back();
            continue;	/* re-iterate */
        }

        specs.push_back (*i);
        ++i;			/* progress */
    }

    debugs(64, 3, "HttpHdrRange::merge: had " << basis.size() <<
           " specs, merged " << basis.size() - specs.size() << " specs");
}