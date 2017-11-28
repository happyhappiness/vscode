void
Ident::IdentStateData::deleteThis(const char *)
{
    swanSong();
    delete this;
}