//
// Created by Vrushhabh Patel on 4/20/21.
//

#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "path_finder_map.h"

namespace pathfinder {
namespace graphics {

class Application : public ci::app::App {
  public:
    /**
     * The actual application that makes the UI of the project
     * The naive-bayes grid lay out made sense for a map so the project is heavily inspired from
     * that
     */
    Application();
    void draw() override;
  private:
    const int kWindowSize = 800;
    const double kMargin = 100;
    const size_t kImageDimension = 30;
    PathFinderMap map_;
};

}  // namespace visualizer

}  // namespace naivebayes



