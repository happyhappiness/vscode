virtual void noteBodyProducerAborted(BodyPipe::Pointer) {
        stopConsumingFrom(body_pipe);
    }