void
Ident::IdentStateData::swanSong()
{
    if (clients != NULL)
        notify(NULL);

    if (Comm::IsConnOpen(conn)) {
        comm_remove_close_handler(conn->fd, Ident::Close, this);
        conn->close();
    }

    hash_remove_link(ident_hash, (hash_link *) this);
    xfree(hash.key);
}