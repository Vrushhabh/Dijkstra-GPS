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
    ci::Color8u background_color(200,200,220); // lavenderish color
    ci::gl::clear(background_color);
    ci::gl::drawStringCentered(
            "Press c to clear the map. Press f to find the path. Right-click to add blocks. "
            "Left-click to add weighted spaces",
            glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

    map_.DrawMap();
}

Application::Application(): map_(glm::vec2(kMargin, kMargin), kImageDimension,
            kWindowSize - 2 * kMargin, .8) {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void Application::mouseDown(ci::app::MouseEvent event) {
    if (event.isRightDown()) {
        map_.AddBlock(event.getPos());
    } else if (event.isLeftDown()) {
        map_.AddWeight(event.getPos());
    }
}

void Application::mouseDrag(ci::app::MouseEvent event) {
    if (event.isRightDown()) {
        map_.AddBlock(event.getPos());
    } else if (event.isLeftDown()) {
        map_.AddWeight(event.getPos());
    }
}

void Application::keyDown(ci::app::KeyEvent event) {
    AppBase::keyDown(event);
    if (event.getCode() == ci::app::KeyEvent::KEY_c) {
        map_.Clear();
    } else if (event.getCode() == ci::app::KeyEvent::KEY_f) {
        Map map = map_.MakeMap();
        map_.FindShortestPath(map);
    }
}
};
}


