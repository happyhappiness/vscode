
extern int rdbCheckMode;
void rdbCheckError(const char *fmt, ...);
void rdbCheckSetError(const char *fmt, ...);

void rdbCheckThenExit(char *reason, int where) {
     if (!rdbCheckMode) {
