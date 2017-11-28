virtual void noteBodyProducerAborted(BodyPipe::Pointer bp) {
        stopConsumingFrom(bp);
        done = true;
    }