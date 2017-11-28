bool
HttpHdrRangeSpec::mergeWith(const HttpHdrRangeSpec * donor)
{
    bool merged (false);
#if MERGING_BREAKS_NOTHING
    /* Note: this code works, but some clients may not like its effects */
    int64_t rhs = offset + length;		/* no -1 ! */
    const int64_t donor_rhs = donor->offset + donor->length;	/* no -1 ! */
    assert(known_spec(offset));
    assert(known_spec(donor->offset));
    assert(length > 0);
    assert(donor->length > 0);
    /* do we have a left hand side overlap? */

    if (donor->offset < offset && offset <= donor_rhs) {
        offset = donor->offset;	/* decrease left offset */
        merged = 1;
    }

    /* do we have a right hand side overlap? */
    if (donor->offset <= rhs && rhs < donor_rhs) {
        rhs = donor_rhs;	/* increase right offset */
        merged = 1;
    }

    /* adjust length if offsets have been changed */
    if (merged) {
        assert(rhs > offset);
        length = rhs - offset;
    } else {
        /* does recepient contain donor? */
        merged =
            offset <= donor->offset && donor->offset < rhs;
    }

#endif
    return merged;
}