/*********************************************************************************
*     File Name           :     online_model.h
*     Created By          :     yuewu
*     Creation Date       :     [2016-02-18 12:52]
*     Last Modified       :     [2016-02-19 00:06]
*     Description         :     online model
**********************************************************************************/
#ifndef LSOL_MODEL_ONLINE_MODEL_H__
#define LSOL_MODEL_ONLINE_MODEL_H__

#include <lsol/model/model.h>
#include <lsol/pario/data_point.h>

namespace lsol {
namespace model {

class OnlineModel : public Model {
 public:
  OnlineModel(int class_num, const std::string& type);

  virtual ~OnlineModel() {}

  /// \brief  set model parameters
  ///
  /// \param name name of the parameter
  /// \param value value of the parameter in string
  virtual void SetParameter(const std::string& name, const std::string& value);

 public:
  /// \brief  Train from a data set
  //
  /// \param data_iter data iterator
  //
  /// \return training error rate
  virtual float Train(pario::DataIter& data_iter);

 public:
  /// \brief  iterate the model with one new instance
  ///
  /// \param x training instance
  /// \param y predicted scores over classes
  ///
  /// \return predicted label
  virtual label_t Iterate(const pario::DataPoint& x, float* y);

 protected:
  /// \brief  Get Model Information
  ///
  /// \param root root node of saver
  /// info
  virtual void GetModelInfo(Json::Value& root) const;

  /// \brief  load model from string
  ///
  /// \param root root node of model info
  ///
  /// \return status code, Status_OK if load successfully
  virtual int SetModelInfo(const Json::Value& root);

 protected:
  void set_power_t(float power_t);
  void set_initial_t(int initial_t);
  virtual void update_dim(index_t dim) { this->dim_ = dim; }

 protected:
  // power_t of the decreasing coefficient of learning rate
  float power_t_;
  // initial learning rate
  float eta0_;
  // initial learning step
  int initial_t_;

  // learning rate
  float eta_;
  // current iteration number
  int cur_iter_num_;

  // dimension of input feature: can be the same to feature, or with an extra
  // bias
  index_t dim_;

  // if true, update  if predicted label is correct, useful for logistic
  // regression
  bool aggressive_;

  float (*pow_)(int iter, float power_t);

};  // class Online Model
}  // namespace model
}  // namespace lsol

#endif
