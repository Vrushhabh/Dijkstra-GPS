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
    ci::Color8u background_color(50,205,50); // light blue
    ci::gl::clear(background_color);
    map_.DrawMap()

}

Application::Application(): map_(glm::vec2(kMargin, kMargin), kImageDimension,
            kWindowSize - 2 * kMargin) {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}


};



}  // namespace visualizer

  // namespace naivebayes


