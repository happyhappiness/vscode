addReplySds(c,sdscatprintf(sdsempty(),
                "+Key at:%p refcount:%d, value swapped at: page %llu "
                "using %llu pages\r\n",
                (void*)key, key->refcount, (unsigned long long) key->vm.page,
                (unsigned long long) key->vm.usedpages));