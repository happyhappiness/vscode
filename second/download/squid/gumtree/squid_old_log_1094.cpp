mb->Printf("\t%d locks, %d clients, %d refs\n",
               (int) e->lock_count,
               storePendingNClients(e),
               (int) e->refcount);