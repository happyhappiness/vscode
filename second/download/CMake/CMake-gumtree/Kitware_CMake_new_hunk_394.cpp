 *                  BEFORE any reading/polling of pipes occurs and before any

 *                  detachment occurs.

 */

int runChild(const char* cmd[], int state, int exception, int value, int share,

             int output, int delay, double timeout, int poll, int repeat,

             int disown, int createNewGroup, unsigned int interruptDelay)

{

  int result = 1;

  kwsysProcess* kp = kwsysProcess_New();

  if (!kp) {

    fprintf(stderr, "kwsysProcess_New returned NULL!\n");

    return 1;

  }

  while (repeat-- > 0) {

    result = runChild2(kp, cmd, state, exception, value, share, output, delay,

                       timeout, poll, disown, createNewGroup, interruptDelay);

    if (result) {

      break;

    }

  }

  kwsysProcess_Delete(kp);

  return result;

}

