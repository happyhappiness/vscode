            printf("ERROR: %s\n", reply->str);
            exit(1);
        } else {
            int j;

            cur = strtoull(reply->element[0]->str,NULL,10);
            for (j = 0; j < reply->element[1]->elements; j++)
