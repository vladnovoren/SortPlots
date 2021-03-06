#include "plot_widget.hpp"

Ranges::Ranges(const double min_x, const double min_y,
               const double max_x, const double max_y):
        min_x_(min_x), min_y_(min_y), max_x_(max_x), max_y_(max_y) {}

glib::Vector2d Ranges::GetSize() const {
  return glib::Vector2d(max_x_ - min_x_, max_y_ - min_y_);
}

double Ranges::GetWidth() const {
  return max_x_ - min_x_;
}

double Ranges::GetHeight() const {
  return max_y_ - min_y_;
}

PlotWidget::PlotWidget(const glib::IntRect &location):
            gui::AbstractWidget(location),
            ranges_(0, 0, location.m_size.x, location.m_size.y) {
  CountCenter();
  render_texture_.Resize(location.m_size);
  Clear();
}

PlotWidget::PlotWidget(const glib::IntRect& location,
                       const Ranges& ranges):
            gui::AbstractWidget(location), ranges_(ranges) {
  ppu_ = static_cast<double>(ranges.GetWidth() / location.m_size.x);
  CountCenter();
  render_texture_.Resize(location.m_size);
  Clear();
}

void PlotWidget::SetPPU(const double ppu) {
  ppu_ = ppu;
}

void PlotWidget::SetRanges(const Ranges& ranges) {
  ranges_ = ranges;
}

double PlotWidget::GetPPU() const {
  return ppu_;
}

const Ranges& PlotWidget::GetRanges() const {
  return ranges_;
}

void PlotWidget::CountCenter() {
  center_.x = ppu_ * fabs(ranges_.min_x_);
  center_.y = ppu_ * fabs(ranges_.max_y_);
}

void PlotWidget::RenderBoundingbox() {
  glib::IntLine upper_line(0, 0.5 * GRAPHICS_BOUNDING_THICKNESS, m_location.m_size.x, 0.5 * GRAPHICS_BOUNDING_THICKNESS, GRAPHICS_BOUNDING_THICKNESS);
  glib::IntLine right_line(m_location.m_size.x - 0.5 * GRAPHICS_BOUNDING_THICKNESS, 0, m_location.m_size.x - 0.5 * GRAPHICS_BOUNDING_THICKNESS, m_location.m_size.y, GRAPHICS_BOUNDING_THICKNESS);
  glib::IntLine lower_line(0, m_location.m_size.y - 0.5 * GRAPHICS_BOUNDING_THICKNESS, m_location.m_size.x, m_location.m_size.y - 0.5 * GRAPHICS_BOUNDING_THICKNESS, GRAPHICS_BOUNDING_THICKNESS);
  glib::IntLine left_line(0.5 * GRAPHICS_BOUNDING_THICKNESS, 0, 0.5 * GRAPHICS_BOUNDING_THICKNESS, m_location.m_size.y ,GRAPHICS_BOUNDING_THICKNESS);

  glib::ColorRGBA black;

  render_texture_.RenderLine(lower_line, black);
  render_texture_.RenderLine(upper_line, black);
  render_texture_.RenderLine(right_line, black);
  render_texture_.RenderLine(left_line, black);

  render_texture_.Display();
}

void PlotWidget::RenderAxes() {
  glib::Vector2i ox_left(GRAPHICS_THICKNESS, center_.y);
  glib::Vector2i ox_right(m_location.m_size.x - GRAPHICS_THICKNESS, center_.y);

  glib::Vector2i oy_upper(center_.x, GRAPHICS_THICKNESS);
  glib::Vector2i oy_lower(center_.x, m_location.m_size.y - GRAPHICS_THICKNESS);

  glib::IntLine ox(ox_left, ox_right, GRAPHICS_THICKNESS);
  glib::IntLine oy(oy_upper, oy_lower, GRAPHICS_THICKNESS);

  glib::ColorRGBA black;

  render_texture_.RenderLine(ox, black);
  render_texture_.RenderLine(oy, black);

  render_texture_.Display();
}

void PlotWidget::Clear() {
  render_texture_.Clear(glib::WHITE);

  RenderBoundingbox();
  RenderAxes();
}

void PlotWidget::Draw(glib::RenderTarget* render_target,
                      const glib::Vector2i& position) {
  assert(render_target != nullptr);

  render_target->CopyRenderTexture(render_texture_, position);
}
