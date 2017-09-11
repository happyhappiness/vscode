                                    size_t type_nbytes,
                                    size_t count,
                                    ReduceFunction reducer) {
  // read from next link and send to prev one 
  LinkRecord &prev = *ring_prev, &next = *ring_next;
  // need to reply on special rank structure
  utils::Assert(next.rank == (rank + 1) % world_size &&
