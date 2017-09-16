#define STANDALONE_MAIN standalone_main



static void standalone_main(int argc, char **argv)

{

    int remaining_children_to_start;



#ifdef OS2

    printf("%s \n", ap_get_server_version());

#endif



    ap_standalone = 1;



    is_graceful = 0;

