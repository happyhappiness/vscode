            zl = ziplistDeleteRange(zl,0,1);
        }
        printf("List size: %8d, bytes: %8d, %dx push+pop (%s): %6lld usec\n",
            i,ZIPLIST_BYTES(zl),num,posstr[pos],usec()-start);
        zfree(zl);
    }
}
