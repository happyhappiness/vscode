inline void
Frame::balance_row(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  // Find the size of the static frames. The dynamic frames are added
  // to a temporary list for the second pass. Each frame uses the
  // m_width and m_height as temporary storage for width and height in
  // this algorithm.
  size_type    dynamicSize = 0;
  dynamic_type dynamicFrames[max_size];

  int remaining = height;
  
  for (Frame **itr = m_container, **last = m_container + m_containerSize; itr != last; ++itr) {
    bounds_type bounds = (*itr)->preferred_size();
    
    if ((*itr)->is_height_dynamic()) {
      (*itr)->m_height = 0;
      dynamicFrames[dynamicSize++] = std::make_pair(*itr, bounds);

    } else {
      (*itr)->m_height = bounds.minHeight;
      remaining -= bounds.minHeight;
    }
  }
  
  // Sort the dynamic frames by the min size in the direction we are
  // interested in. Then try to satisfy the largest first, and if we
  // have any remaining space we can use that to extend it and any
  // following frames.
  //
  // Else if we're short, only give each what they require.
  std::sort(dynamicFrames, dynamicFrames + dynamicSize,
            rak::greater2(rak::on(rak::const_mem_ref(&dynamic_type::second), rak::const_mem_ref(&Frame::bounds_type::minHeight)),
                          rak::on(rak::const_mem_ref(&dynamic_type::second), rak::const_mem_ref(&Frame::bounds_type::minHeight))));

  bool retry;

  do {
    retry = false;

    for (dynamic_type *itr = dynamicFrames, *last = dynamicFrames + dynamicSize; itr != last; ++itr) {
      uint32_t adjust = (std::max(remaining, 0) + std::distance(itr, last) - 1) / std::distance(itr, last);
    
      adjust += itr->first->m_height;
      adjust = std::max(adjust, itr->second.minHeight);
      adjust = std::min(adjust, itr->second.maxHeight);
        
      remaining -= adjust - itr->first->m_height;

      retry = retry || itr->first->m_height != adjust;

      itr->first->m_height = adjust;
    }

  } while (retry && remaining > 0);

  // Use the pre-calculated frame sizes to balance the sub-frames. If
  // the frame is too small, it will set the remaining windows to zero
  // extent which will flag them as offscreen.

  for (Frame **itr = m_container, **last = m_container + m_containerSize; itr != last; ++itr) {
    // If there is any remaining space, check if we want to shift
    // the subsequent frames to the other side of this frame.
    if (remaining > 0 && (*itr)->has_bottom_frame()) {
      (*itr)->m_height += remaining;
      remaining = 0;
    }

    (*itr)->balance(x, y, m_width, std::min((*itr)->m_height, height));

    y += (*itr)->m_height;
    height -= (*itr)->m_height;
  }
}