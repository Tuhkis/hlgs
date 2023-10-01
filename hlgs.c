#define HL_NAME(n) hlgs_##n
#include "hl.h"

#include "gunslinger/gs.h"

static void _init() {}
static void _frame() {}
static void _cleanup() {}

HL_PRIM void HL_NAME(create) (vdynamic* app) {
  gs_app_desc_t a;
  a.window.width = hl_dyn_geti(app, hl_hash_utf8("width"), &hlt_i32);
  a.window.height = hl_dyn_geti(app, hl_hash_utf8("height"), &hlt_i32);
  // vstring* s = hl_dyn_getp(app, hl_hash_utf8("title"), &hlt_bytes);
  // printf(s->bytes);

  a.window.title = "Cant set custom title yet.";

  a.window.vsync = true;
  a.window.frame_rate = 60;
  a.init = _init;
  a.update = _frame;
  a.shutdown = _cleanup;
  gs_create(a);
  while (gs_app()->is_running) {
    gs_frame();
  }
}

HL_PRIM bool HL_NAME(app_is_running) () { return gs_app()->is_running; }

HL_PRIM void HL_NAME(frame) () { gs_frame(); }

DEFINE_PRIM(_VOID, create, _DYN);
DEFINE_PRIM(_BOOL, app_is_running, _NO_ARG);
DEFINE_PRIM(_VOID, frame, _NO_ARG);

