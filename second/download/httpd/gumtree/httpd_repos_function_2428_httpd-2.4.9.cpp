static void slotmem_clearinuse(ap_slotmem_instance_t *slot)
{
    unsigned int i;
    char *inuse;
    
    if (!slot) {
        return;
    }
    
    inuse = slot->inuse;
    
    for (i = 0; i < slot->desc.num; i++, inuse++) {
        if (*inuse) {
            *inuse = 0;
            (*slot->num_free)++;
        }
    }
}