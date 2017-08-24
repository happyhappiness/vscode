f(h->table[i].head) {
        iter->current_element = h->table[i].head;
        iter->slot_index = i+1;
        break;
      }