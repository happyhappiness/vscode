{
                struct links_entry *lp = cpio->links_head->next;

                if (cpio->links_head->name)
                        free(cpio->links_head->name);
                free(cpio->links_head);
                cpio->links_head = lp;
        }