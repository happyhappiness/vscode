            robj *val;

            /* Key swapped. We can finally free some memory. */
            val = dictGetEntryVal(de);
            key->vm.page = j->page;
            key->vm.usedpages = j->pages;
