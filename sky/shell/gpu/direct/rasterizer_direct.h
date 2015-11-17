// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SKY_SHELL_GPU_DIRECT_RASTERIZER_H_
#define SKY_SHELL_GPU_DIRECT_RASTERIZER_H_

#include "base/memory/weak_ptr.h"
#include "skia/ext/refptr.h"
#include "sky/compositor/paint_context.h"
#include "sky/shell/gpu/ganesh_canvas.h"
#include "sky/shell/rasterizer.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/native_widget_types.h"

namespace gfx {
class GLContext;
class GLShareGroup;
class GLSurface;
}

namespace sky {
namespace shell {
class GaneshContext;
class GaneshSurface;

class RasterizerDirect : public Rasterizer {
 public:
  explicit RasterizerDirect();
  ~RasterizerDirect() override;

  base::WeakPtr<RasterizerDirect> GetWeakPtr();
  RasterCallback GetRasterCallback() override;

  void OnAcceleratedWidgetAvailable(gfx::AcceleratedWidget widget);
  void OnOutputSurfaceDestroyed();

 private:
  void Draw(scoped_ptr<compositor::LayerTree> layer_tree);
  void EnsureGLContext();
  void EnsureGaneshSurface(intptr_t window_fbo, const gfx::Size& size);

  scoped_refptr<gfx::GLShareGroup> share_group_;
  scoped_refptr<gfx::GLSurface> surface_;
  scoped_refptr<gfx::GLContext> context_;

  skia::RefPtr<const GrGLInterface> gr_gl_interface_;
  GaneshCanvas ganesh_canvas_;

  compositor::PaintContext paint_context_;

  base::WeakPtrFactory<RasterizerDirect> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RasterizerDirect);
};

}  // namespace shell
}  // namespace sky

#endif  // SKY_SHELL_GPU_DIRECT_RASTERIZER_H_