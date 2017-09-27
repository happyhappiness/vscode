                 * succeeds, get the context off the queue. It must be
                 * available, since there's only one consumer.
                 */
                rv = WaitForSingleObject(qwait_event, 1000);
                if (rv == WAIT_OBJECT_0)
                    continue;
                else /* Hopefully, WAIT_TIMEOUT */
                    return NULL;
            } else {
                /* Allocate another context.
                 * Note: Multiple failures in the next two steps will cause
                 * the pchild pool to 'leak' storage. I don't think this
                 * is worth fixing...
                 */
