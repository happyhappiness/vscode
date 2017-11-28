void
ESIVariableProcessor::doIt()
{
    assert (output == NULL);

    while (pos < len) {
        /* skipping pre-variables */

        if (string[pos] != '$') {
            ++pos;
        } else {
            if (pos - done_pos)
                /* extract known plain text */
                ESISegment::ListAppend (output, string + done_pos, pos - done_pos);

            done_pos = pos;

            ++pos;

            identifyFunction();

            doFunction();
        }
    }

    /* pos-done_pos chars are ready to copy */
    if (pos-done_pos)
        ESISegment::ListAppend (output, string+done_pos, pos - done_pos);

    safe_free (found_default);

    safe_free (found_subref);
}