const SquidTLV*
SquidMetaList::search( SquidMetaType type ) const
{
    const SquidTLV* temp = head;
    while ( temp && temp->type != type ) temp = temp->next;
    return temp;
}