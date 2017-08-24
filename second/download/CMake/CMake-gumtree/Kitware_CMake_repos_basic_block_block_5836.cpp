f(curr->ptr == handle) {
        Curl_llist_remove(pipeline, curr, NULL);
        return 1; /* we removed a handle */
      }