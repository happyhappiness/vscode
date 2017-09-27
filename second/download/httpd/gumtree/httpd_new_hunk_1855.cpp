        }
    }

    return context;
}


/* Windows NT/2000 specific code...
 * Accept processing for on Windows NT uses a producer/consumer queue
 * model. An accept thread accepts connections off the network then issues
 * PostQueuedCompletionStatus() to awake a thread blocked on the ThreadDispatch
 * IOCompletionPort.
