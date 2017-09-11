void Dump(int nid, std::stringstream &fo, // NOLINT(*)
            const utils::FeatMap& fmap, int depth, bool with_stats) {
    for (int i = 0;  i < depth; ++i) {
      fo << '\t';
    }
    if (nodes[nid].is_leaf()) {
      fo << nid << ":leaf=" << nodes[nid].leaf_value();
      if (with_stats) {
        stat(nid).Print(fo, true);
      }
      fo << '\n';
    } else {
      // right then left,
      TSplitCond cond = nodes[nid].split_cond();
      const unsigned split_index = nodes[nid].split_index();
      if (split_index < fmap.size()) {
        switch (fmap.type(split_index)) {
          case utils::FeatMap::kIndicator: {
            int nyes = nodes[nid].default_left() ?
                nodes[nid].cright() : nodes[nid].cleft();
            fo << nid << ":[" << fmap.name(split_index) << "] yes=" << nyes
               << ",no=" << nodes[nid].cdefault();
            break;
          }
          case utils::FeatMap::kInteger: {
            fo << nid << ":[" << fmap.name(split_index) << "<"
               << int(float(cond)+1.0f)
               << "] yes=" << nodes[nid].cleft()
               << ",no=" << nodes[nid].cright()
               << ",missing=" << nodes[nid].cdefault();
            break;
          }
          case utils::FeatMap::kFloat:
          case utils::FeatMap::kQuantitive: {
            fo << nid << ":[" << fmap.name(split_index) << "<"<< float(cond)
               << "] yes=" << nodes[nid].cleft()
               << ",no=" << nodes[nid].cright()
               << ",missing=" << nodes[nid].cdefault();
            break;
          }
          default: utils::Error("unknown fmap type");
        }
      } else {
        fo << nid << ":[f" << split_index << "<"<< float(cond)
           << "] yes=" << nodes[nid].cleft()
           << ",no=" << nodes[nid].cright()
           << ",missing=" << nodes[nid].cdefault();
      }
      if (with_stats) {
        stat(nid).Print(fo, false);
      }
      fo << '\n';
      this->Dump(nodes[nid].cleft(), fo, fmap, depth+1, with_stats);
      this->Dump(nodes[nid].cright(), fo, fmap, depth+1, with_stats);
    }
  }