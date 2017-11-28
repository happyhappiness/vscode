    virtual void abortTransaction(const char *reason) = 0;

    /// a hack to reach HttpStateData::orignal_request
    virtual  HttpRequest *originalRequest();

#if USE_ADAPTATION
    void adaptationAclCheckDone(Adaptation::ServiceGroupPointer group);
    static void adaptationAclCheckDoneWrapper(Adaptation::ServiceGroupPointer group, void *data);

    // ICAPInitiator: start an ICAP transaction and receive adapted headers.
    virtual void noteAdaptationAnswer(HttpMsg *message);
    virtual void noteAdaptationQueryAbort(bool final);

    // BodyProducer: provide virgin response body to ICAP.
    virtual void noteMoreBodySpaceAvailable(BodyPipe::Pointer );
    virtual void noteBodyConsumerAborted(BodyPipe::Pointer );
#endif
    virtual void processReplyBody() = 0;

//AsyncJob virtual methods
    virtual void swanSong();
    virtual bool doneAll() const {
        return
#if USE_ADAPTATION
            Adaptation::Initiator::doneAll() &&
            BodyProducer::doneAll() &&
#endif
            BodyConsumer::doneAll() && false;
    }

public: // should be protected
    void serverComplete();     /**< call when no server communication is expected */

private:
    void serverComplete2();    /**< Continuation of serverComplete */
