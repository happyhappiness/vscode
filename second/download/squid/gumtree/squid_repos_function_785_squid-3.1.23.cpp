MemBuf *
HttpReply::packed304Reply()
{
    /* Not as efficient as skipping the header duplication,
     * but easier to maintain
     */
    HttpReply *temp = make304 ();
    MemBuf *rv = temp->pack();
    delete temp;
    return rv;
}