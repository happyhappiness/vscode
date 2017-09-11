                 * \param index, the index of retrieved instance
                 * \return the index of instances paired
                 */
                std::vector<int> GetPairs(int index) const{
                    utils::Assert(index >= start_ && index < end_, "The query index out of sampling bound");
                    return pairs_[index - start_];
                }
