void
SquidMetaList::append( SquidMetaType type, size_t size, void* data )
{
    SquidTLV* temp = new SquidTLV( type, size, data );
    if ( head == 0 ) head = tail = temp;
    else {
        tail->next = temp;
        tail = temp;
    }
}