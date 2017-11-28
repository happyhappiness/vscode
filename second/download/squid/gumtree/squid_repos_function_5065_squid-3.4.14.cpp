void
Ident::IdentStateData::deleteThis(const char *aReason)
{
    swanSong();
    delete this;
}