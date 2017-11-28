static void
squidaio_poll_queues(void)
{
    /* kick "overflow" request queue */

    if (request_queue2.head &&
            pthread_mutex_trylock(&request_queue.mutex) == 0) {
        *request_queue.tailp = request_queue2.head;
        request_queue.tailp = request_queue2.tailp;
        pthread_cond_signal(&request_queue.cond);
        pthread_mutex_unlock(&request_queue.mutex);
        request_queue2.head = NULL;
        request_queue2.tailp = &request_queue2.head;
    }

    /* poll done queue */
    if (done_queue.head && pthread_mutex_trylock(&done_queue.mutex) == 0) {

        struct squidaio_request_t *requests = done_queue.head;
        done_queue.head = NULL;
        done_queue.tailp = &done_queue.head;
        pthread_mutex_unlock(&done_queue.mutex);
        *done_requests.tailp = requests;
        request_queue_len -= 1;

        while (requests->next) {
            requests = requests->next;
            request_queue_len -= 1;
        }

        done_requests.tailp = &requests->next;
    }
}