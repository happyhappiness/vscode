int
HttpHdrRangeSpec::canonize(int64_t clen)
{
    outputInfo ("have");
    HttpRange object(0, clen);

    if (!known_spec(offset)) {  /* suffix */
        assert(known_spec(length));
        offset = object.intersection(HttpRange (clen - length, clen)).start;
    } else if (!known_spec(length)) {   /* trailer */
        assert(known_spec(offset));
        HttpRange newRange = object.intersection(HttpRange (offset, clen));
        length = newRange.size();
    }
    /* we have a "range" now, adjust length if needed */
    assert(known_spec(length));

    assert(known_spec(offset));

    HttpRange newRange = object.intersection (HttpRange (offset, offset + length));

    length = newRange.size();

    outputInfo ("done");

    return length > 0;
}