void addReply(redisClient *c, robj *obj) {
    if (_ensureFileEvent(c) != REDIS_OK) return;
    if (server.vm_enabled && obj->storage != REDIS_VM_MEMORY) {
        /* Returns a new object with refcount 1 */
        obj = dupStringObject(obj);
    } else {
        /* This increments the refcount. */
        obj = getDecodedObject(obj);
    }

    if (sdslen(obj->ptr) < REDIS_REPLY_CHUNK_THRESHOLD) {
        _addReplyStringToBuffer(c,obj->ptr,sdslen(obj->ptr));
        decrRefCount(obj);
    } else {
        _addReplyObjectToList(c,obj);
    }
}