void
HttpBody::setMb(MemBuf * mb_)
{
    delete mb;
    /* note: protection against assign-to-self is not needed
     * as MemBuf doesn't have a copy-constructor. If such a constructor
     * is ever added, add such protection here.
     */
    mb = mb_;       /* absorb */
}