static unsigned int slotmem_num_free_slots(ap_slotmem_instance_t *slot)
{
    if (AP_SLOTMEM_IS_PREGRAB(slot))
        return *slot->num_free;
    else {
        unsigned int i, counter=0;
        char *inuse = slot->inuse;
        for (i=0; i<slot->desc.num; i++, inuse++) {
            if (!*inuse)
                counter++;
        }
        return counter;
    }
}