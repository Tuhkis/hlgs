#define HL_NAME(n) hlgs_##n
#include "hl.h"

#include "gunslinger/gs.h"

static void _hlgs_init() {}
static void _hlgs_frame() {}
static void _hlgs_cleanup() {}

HL_PRIM void HL_NAME(create_ex) (vdynamic* app, vbyte* title, int title_len) {
  gs_app_desc_t a;
  a.window.width = hl_dyn_geti(app, hl_hash_utf8("width"), &hlt_i32);
  a.window.height = hl_dyn_geti(app, hl_hash_utf8("height"), &hlt_i32);

  char title_buf[title_len + 1];
  for (int i = 0; i < title_len; ++i)
    title_buf[i] = *(title + i * 2);
  title_buf[title_len] = 0;

  a.window.title = title_buf;

  a.window.vsync = hl_dyn_geti(app, hl_hash_utf8("vsync"), &hlt_i32);
  a.window.frame_rate = hl_dyn_geti(app, hl_hash_utf8("fps"), &hlt_i32);
  a.init = _hlgs_init;
  a.update = _hlgs_frame;
  a.shutdown = _hlgs_cleanup;
  gs_create(a);
}

HL_PRIM bool HL_NAME(app_is_running) () { return gs_app()->is_running; }

HL_PRIM void HL_NAME(frame) () { gs_frame(); }

DEFINE_PRIM(_VOID, create_ex, _DYN _BYTES _I32);
DEFINE_PRIM(_BOOL, app_is_running, _NO_ARG);
DEFINE_PRIM(_VOID, frame, _NO_ARG);

