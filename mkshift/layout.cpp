#include "layout.hpp"

Element::Element() {
  this->ygnode = YGNodeNew();
}

Element::~Element() {
  YGNodeFree(this->ygnode);
}

void Element::addChild(Element *child) {
  child->parent = this;
  
  this->children.push_back(child);
  
  YGNodeRemoveAllChildren(this->ygnode);

  for (size_t i = 0; i < this->children.size(); i++) {
    YGNodeInsertChild(this->ygnode, this->children[i]->ygnode, i);
  }
}

void Element::removeAllChildren() {
  this->children.clear();
}

void Element::recalc(double available_width, double available_height, YGDirection ownerdirection) {
  YGNodeCalculateLayout(this->ygnode, available_width, available_height, ownerdirection);
}

aabb Element::asAABB() {
  return aabb {
    YGNodeLayoutGetLeft(this->ygnode),
    YGNodeLayoutGetTop(this->ygnode),
    YGNodeLayoutGetWidth(this->ygnode),
    YGNodeLayoutGetHeight(this->ygnode)
  };
}

void Element::draw(cairo_t *cr) {
  printf("Element: ");
  this->predraw(cr);
  this->drawChildren(cr);
  this->postdraw(cr);
}

void Element::drawChildren(cairo_t *cr) { 
  for (auto& child : this->children) {
    child->draw(cr);
  }
}

void Element::predraw(cairo_t *cr) {
  cairo_set_source_rgba(cr, this->color.r, this->color.g, this->color.b, this->color.a);

  print_aabb(this->asAABB());
}

void Element::postdraw(cairo_t *cr) {
  (void) cr;
}

Element *Element::getRoot() {
  Element *target = this;

  while (target->parent != nullptr) {
    target = target->parent;
  }

  return target;
}

void cairo_rounded_rectangle(cairo_t *cr, double x, double y, double width, double height, double radius) {
  if (radius == 0) {
    cairo_rectangle(cr, x, y, width, height);
    
    return;
  }
  
  double degrees = M_PI / 180.0;

  cairo_new_sub_path(cr);
  cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
  cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
  cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
  cairo_close_path(cr);
}

Box::Box() {

}

Box::Box(double radius) {
  this->radius = radius;
}

void Box::draw(cairo_t *cr) {
  this->predraw(cr);
  
  aabb bb = this->asAABB();
  cairo_rounded_rectangle(cr, bb.x, bb.y, bb.width, bb.height, this->radius);
  cairo_fill(cr);

  printf("RoundedRect: ");
  this->drawChildren(cr);
}
