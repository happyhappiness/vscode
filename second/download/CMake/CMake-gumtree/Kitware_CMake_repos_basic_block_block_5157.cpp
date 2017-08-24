{
        /* Since there's a new easy handle at the start of the send pipeline,
           set its timeout value to 1ms to make it trigger instantly */
        Curl_pipeline_leave_write(conn); /* not used now */
#ifdef DEBUGBUILD
        infof(conn->data, "%p is at send pipe head B!\n",
              (void *)conn->send_pipe.head->ptr);
#endif
        Curl_expire(conn->send_pipe.head->ptr, 0, EXPIRE_RUN_NOW);
      }