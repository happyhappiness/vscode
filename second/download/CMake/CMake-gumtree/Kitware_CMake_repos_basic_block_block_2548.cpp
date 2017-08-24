(repeat-- > 0) {
    result = runChild2(kp, cmd, state, exception, value, share, output, delay,
                       timeout, poll, disown, createNewGroup, interruptDelay);
    if (result) {
      break;
    }
  }