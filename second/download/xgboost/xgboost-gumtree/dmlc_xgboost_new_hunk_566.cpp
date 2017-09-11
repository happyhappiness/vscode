  /*!
   * \brief peform update to the tree models
   * \param gpair the gradient pair statistics of the data
   * \param p_fmat feature matrix that provide access to features
   * \param info extra side information that may be need, such as root index
   * \param trees pointer to the trese to be updated, upater will change the content of the tree
   *   note: all the trees in the vector are updated, with the same statistics, 
   *         but maybe different random seeds, usually one tree is passed in at a time, 
   *         there can be multiple trees when we train random forest style model
   */
  virtual void Update(const std::vector<bst_gpair> &gpair,
                      IFMatrix *p_fmat,
                      const BoosterInfo &info,
                      const std::vector<RegTree*> &trees) = 0;
  // destructor
  virtual ~IUpdater(void) {}
};
/*! 
 * \brief create a updater based on name 
 * \param name name of updater
 * \return return the updater instance
 */
IUpdater* CreateUpdater(const char *name);
}  // namespace tree
}  // namespace xgboost
#endif  // XGBOOST_TREE_UPDATER_H_
