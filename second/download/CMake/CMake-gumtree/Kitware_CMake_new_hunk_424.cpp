              statename[data->mstate], data->numsocks);

      for(i=0; i < data->numsocks; i++) {

        curl_socket_t s = data->sockets[i];

        struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);



        fprintf(stderr, "%d ", (int)s);

        if(!entry) {
