printf("Thread %lld got a new job: %p about key '%s'\n",
            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);