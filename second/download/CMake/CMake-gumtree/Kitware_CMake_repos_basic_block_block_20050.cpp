{
          req = uv_overlapped_to_req(overlappeds[i].lpOverlapped);
          uv_insert_pending_req(loop, req);
        }