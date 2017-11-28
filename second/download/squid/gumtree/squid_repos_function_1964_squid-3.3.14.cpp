virtual void noteMoreBodyDataAvailable(BodyPipe::Pointer bp) {
        size_t contentSize = bp->buf().contentSize();
        bp->consume(contentSize);
    }