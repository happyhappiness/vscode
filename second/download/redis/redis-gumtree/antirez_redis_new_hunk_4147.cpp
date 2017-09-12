
/* =================== Virtual Memory - Blocking Side  ====================== */

static void vmInit(void) {
    off_t totsize;
    int pipefds[2];
