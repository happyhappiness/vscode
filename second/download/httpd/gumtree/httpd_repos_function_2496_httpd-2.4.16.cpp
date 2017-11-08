static unsigned int slotmem_num_free_slots(ap_slotmem_instance_t *slot)
{
    unsigned int i, counter=0;
    char *inuse = slot->inuse;
    for (i = 0; i < slot->num; i++, inuse++) {
        if (!*inuse)
            counter++;
    }
    return counter;
}