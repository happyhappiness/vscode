                        fatalf("Unknown service hash method\n");
                    }

                    value_element->cache_ip = cache_list_ptr->cache_ip;

                    offset += sizeof(struct wccp2_value_element_t);
                    value++;

                    /* Assign the next value to the next cache */

                    if ((cache_list_ptr->next) && (cache_list_ptr->next->next))
                        cache_list_ptr = cache_list_ptr->next;
                    else
