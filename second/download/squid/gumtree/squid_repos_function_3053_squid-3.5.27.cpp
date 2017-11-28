const cache_key *StoreEntry::calcPublicKey(const KeyScope keyScope) {
    assert(mem_obj);
    return mem_obj->request ?  storeKeyPublicByRequest(mem_obj->request, keyScope) :
           storeKeyPublic(mem_obj->storeId(), mem_obj->method, keyScope);
}