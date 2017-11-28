virtual void fire() {
        fired = true;
        AsyncCallT<AnswerDialer>::fire();
    }