#ifndef I_PLOT_FUNCTOR_HPP
#define I_PLOT_FUNCTOR_HPP

#include "gui.hpp"
#include "plot_widget.hpp"

class IPlotFunctor: public gui::AbstractWidgetFunctor {
 public:
  IPlotFunctor() = default;
  IPlotFunctor(PlotWidget* plot_widget);

  void SetPlotWidget(PlotWidget* plot_widget);
  PlotWidget* GetPlotWidget() const;

 protected:
  PlotWidget* plot_widget_ = nullptr;
};

#endif /* i_plot_functor.hpp */
