            }
            snprintf(buf,sizeof(buf),"value:%lu",j);
            val = createStringObject(buf,strlen(buf));
            dictAdd(c->db->dict,key,val);
        }
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {
