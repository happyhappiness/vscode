void
StoreEntry::reset()
{
    assert (mem_obj);
    debugs(20, 3, "StoreEntry::reset: " << url());
    mem_obj->reset();
    HttpReply *rep = (HttpReply *) getReply();       // bypass const
    rep->reset();
    expires = lastModified_ = timestamp = -1;
}