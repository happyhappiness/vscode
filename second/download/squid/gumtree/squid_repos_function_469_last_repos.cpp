int
HttpReply::validatorsMatch(HttpReply const * otherRep) const
{
    String one,two;
    assert (otherRep);
    /* Numbers first - easiest to check */
    /* Content-Length */
    /* TODO: remove -1 bypass */

    if (content_length != otherRep->content_length
            && content_length > -1 &&
            otherRep->content_length > -1)
        return 0;

    /* ETag */
    one = header.getStrOrList(Http::HdrType::ETAG);

    two = otherRep->header.getStrOrList(Http::HdrType::ETAG);

    if (one.size()==0 || two.size()==0 || one.caseCmp(two)!=0 ) {
        one.clean();
        two.clean();
        return 0;
    }

    if (last_modified != otherRep->last_modified)
        return 0;

    /* MD5 */
    one = header.getStrOrList(Http::HdrType::CONTENT_MD5);

    two = otherRep->header.getStrOrList(Http::HdrType::CONTENT_MD5);

    if (one.size()==0 || two.size()==0 || one.caseCmp(two)!=0 ) {
        one.clean();
        two.clean();
        return 0;
    }

    return 1;
}