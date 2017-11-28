virtual void noteBodyProductionEnded(BodyPipe::Pointer) {
        stopConsumingFrom(body_pipe);
    }