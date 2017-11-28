/** temporary thunk across to the unrefactored store interface */

class StoreRootEngine : public AsyncEngine
{

public:
    int checkEvents(int timeout) {
        Store::Root().callback();
        return EVENT_IDLE;
    };
};

class SignalEngine: public AsyncEngine
{

public:
    virtual int checkEvents(int timeout);

private:
    static void StopEventLoop(void *) {
        if (EventLoop::Running)
            EventLoop::Running->stop();
