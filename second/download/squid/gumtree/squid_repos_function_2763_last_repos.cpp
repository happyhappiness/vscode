void
memNodeWriteComplete(void* d)
{
    mem_node* n = (mem_node*)((char*)d - _mem_node_data_offset);
    assert(n->write_pending);
    n->write_pending = false;
}