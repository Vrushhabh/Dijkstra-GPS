//
// Created by Vrushhabh Patel on 4/20/21.
//

#include "../../include/graphics/application.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace pathfinder {
namespace graphics {
void Application::draw() {
    ci::Color8u background_color(200,200,220); // light green
    ci::gl::clear(background_color);
    map_.DrawMap();
}

Application::Application(): map_(glm::vec2(kMargin, kMargin), kImageDimension,
            kWindowSize - 2 * kMargin, .8) {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void Application::mouseDown(ci::app::MouseEvent event) {
    map_.BlockBrush(event.getPos());
}

};
}  // namespace visualizer

  // namespace naivebayes


