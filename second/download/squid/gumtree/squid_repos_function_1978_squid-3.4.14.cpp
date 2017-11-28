virtual void noteBodyProducerAborted(BodyPipe::Pointer bp) {
        stopConsumingFrom(body_pipe);
    }