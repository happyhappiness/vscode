	}
	j++;
      } while (j<s->count && targets[j].t == t);
    }

    /* Trim off the first byte from the checksum */
    map = map_ptr(buf,offset,k+1);
    s1 -= map[0];
    s2 -= k * map[0];

    /* Add on the next byte (if there is one) to the checksum */
    if (k < (len-offset)) {
      s1 += map[k];
      s2 += s1;
    } else {
      --k;
    }

  } while (++offset < end);

  matched(f,s,buf,len,len,-1);
}


