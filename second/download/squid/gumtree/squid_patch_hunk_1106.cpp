     virtual bool getMoreRequestBody(MemBuf &buf);
     virtual void closeServer(); // end communication with the server
     virtual bool doneWithServer() const; // did we end communication?
     virtual void abortAll(const char *reason); // abnormal termination
     virtual bool mayReadVirginReplyBody() const;
 
+    void abortTransaction(const char *reason) { abortAll(reason); } // abnormal termination
+
+    /**
+     * determine if read buffer can have space made available
+     * for a read.
+     *
+     * \param grow  whether to actually expand the buffer
+     *
+     * \return whether the buffer can be grown to provide space
+     *         regardless of whether the grow actually happened.
+     */
+    bool maybeMakeSpaceAvailable(bool grow);
+
     // consuming request body
     virtual void handleMoreRequestBodyAvailable();
     virtual void handleRequestBodyProducerAborted();
 
-    void abortTransaction(const char *reason) { abortAll(reason); } // abnormal termination
     void writeReplyBody();
     bool decodeAndWriteReplyBody();
     bool finishingBrokenPost();
     bool finishingChunkedRequest();
     void doneSendingRequestBody();
     void requestBodyHandler(MemBuf &);
