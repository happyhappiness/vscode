virtual void noteBodyProductionEnded(BodyPipe::Pointer bp) {
        stopConsumingFrom(bp);
        done = true;
    }