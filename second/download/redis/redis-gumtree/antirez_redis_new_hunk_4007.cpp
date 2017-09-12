 * as a fully non-blocking VM.
 */

/* =================== Virtual Memory - Blocking Side  ====================== */

/* Create a VM pointer object. This kind of objects are used in place of
 * values in the key -> value hash table, for swapped out objects. */
static vmpointer *createVmPointer(int vtype) {
    vmpointer *vp = zmalloc(sizeof(vmpointer));

    vp->type = REDIS_VMPOINTER;
    vp->storage = REDIS_VM_SWAPPED;
    vp->vtype = vtype;
    return vp;
}

static void vmInit(void) {
    off_t totsize;
    int pipefds[2];
