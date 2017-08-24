f(curr->ptr == handle) {
      Curl_llist_move(&conn->send_pipe, curr,
                      &conn->recv_pipe, conn->recv_pipe.tail);

      if(conn->send_pipe.head) {
        /* Since there's a new easy handle at the start of the send pipeline,
           set its timeout value to 1ms to make it trigger instantly */
        Curl_pipeline_leave_write(conn); /* not used now */
#ifdef DEBUGBUILD
        infof(conn->data, "%p is at send pipe head B!\n",
              (void *)conn->send_pipe.head->ptr);
#endif
        Curl_expire(conn->send_pipe.head->ptr, 0, EXPIRE_RUN_NOW);
      }

      /* The receiver's list is not really interesting here since either this
         handle is now first in the list and we'll deal with it soon, or
         another handle is already first and thus is already taken care of */

      break; /* we're done! */
    }