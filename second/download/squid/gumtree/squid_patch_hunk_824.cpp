 
     virtual void start();
     virtual void haveParsedReplyHeaders();
     virtual bool getMoreRequestBody(MemBuf &buf);
     virtual void closeServer(); // end communication with the server
     virtual bool doneWithServer() const; // did we end communication?
-    virtual void abortTransaction(const char *reason); // abnormal termination
+    virtual void abortAll(const char *reason); // abnormal termination
+    virtual bool mayReadVirginReplyBody() const;
 
     // consuming request body
     virtual void handleMoreRequestBodyAvailable();
     virtual void handleRequestBodyProducerAborted();
 
+    void abortTransaction(const char *reason) { abortAll(reason); } // abnormal termination
     void writeReplyBody();
     bool decodeAndWriteReplyBody();
     bool finishingBrokenPost();
     bool finishingChunkedRequest();
     void doneSendingRequestBody();
     void requestBodyHandler(MemBuf &);
