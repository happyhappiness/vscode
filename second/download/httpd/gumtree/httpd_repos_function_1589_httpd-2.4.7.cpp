static int variantsortf(var_rec *a, var_rec *b) {

    /* First key is the source quality, sort in descending order. */

    /* XXX: note that we currently implement no method of setting the
     * source quality for multiviews variants, so we are always comparing
     * 1.0 to 1.0 for now
     */
    if (a->source_quality < b->source_quality)
        return 1;
    if (a->source_quality > b->source_quality)
        return -1;

    /* Second key is the variant name */
    return strcmp(a->file_name, b->file_name);
}