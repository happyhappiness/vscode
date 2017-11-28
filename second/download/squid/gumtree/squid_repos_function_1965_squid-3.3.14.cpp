virtual void noteBodyProductionEnded(BodyPipe::Pointer bp) {
        stopConsumingFrom(body_pipe);
    }