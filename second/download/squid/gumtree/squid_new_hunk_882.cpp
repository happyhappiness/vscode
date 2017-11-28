 */
class Store : public RefCountable
{

public:
    /** The root store */
    static Store &Root() {
        if (CurrentRoot == NULL)
            fatal("No Store Root has been set");
        return *CurrentRoot;
    }
    static void Root(Store *);
    static void Root(RefCount<Store>);
    static void Stats(StoreEntry * output);
    static void Maintain(void *unused);

    virtual ~Store() {}
