    pthread_mutex_unlock(&server.io_mutex);
}

void *IOThreadEntryPoint(void *arg) {
    iojob *j;
    listNode *ln;
