bool
MemObject::isContiguous() const
{
    bool result = data_hdr.hasContigousContentRange (Range<int64_t>(inmem_lo, endOffset()));
    /* XXX : make this higher level */
    debugs (19, result ? 4 :3, "MemObject::isContiguous: Returning " << (result ? "true" : "false"));
    return result;
}