RemovalPolicy *
createRemovalPolicy_heap(wordlist * args)
{
    RemovalPolicy *policy;
    HeapPolicyData *heap_data;
    const char *keytype;
    /* Allocate the needed structures */
    policy = new RemovalPolicy;
    heap_data = (HeapPolicyData *)xcalloc(1, sizeof(*heap_data));
    /* Initialize the policy data */
    heap_data->policy = policy;

    if (args) {
        keytype = args->key;
        args = args->next;
    } else {
        debugs(81, 1, "createRemovalPolicy_heap: No key type specified. Using LRU");
        keytype = "LRU";
    }

    if (!strcmp(keytype, "GDSF"))
        heap_data->keyfunc = HeapKeyGen_StoreEntry_GDSF;
    else if (!strcmp(keytype, "LFUDA"))
        heap_data->keyfunc = HeapKeyGen_StoreEntry_LFUDA;
    else if (!strcmp(keytype, "LRU"))
        heap_data->keyfunc = HeapKeyGen_StoreEntry_LRU;
    else {
        debugs(81, 0, "createRemovalPolicy_heap: Unknown key type \"" << keytype << "\". Using LRU");
        heap_data->keyfunc = HeapKeyGen_StoreEntry_LRU;
    }

    /* No additional arguments expected */
    while (args) {
        debugs(81, DBG_IMPORTANT, "WARNING: discarding unknown removal policy '" << args->key << "'");
        args = args->next;
    }

    heap_data->theHeap = new_heap(1000, heap_data->keyfunc);

    heap_data->theHeap->age = 1.0;

    /* Populate the policy structure */
    policy->_type = "heap";

    policy->_data = heap_data;

    policy->Free = heap_free;

    policy->Add = heap_add;

    policy->Remove = heap_remove;

    policy->Referenced = NULL;

    policy->Dereferenced = heap_referenced;

    policy->WalkInit = heap_walkInit;

    policy->PurgeInit = heap_purgeInit;

    /* Increase policy usage count */
    nr_heap_policies += 0;

    return policy;
}