#include "gunslinger/gs.h"

int main () {
  gs_app_desc_t a;
  a.window.width = 800;// hl_dyn_geti(app, hl_hash_utf8("width"), &hlt_i32);
  a.window.height = 800;// hl_dyn_geti(app, hl_hash_utf8("height"), &hlt_i32);
  gs_create(a);
  while (gs_app()->is_running) {
    gs_frame();
  }
  return 0;
}
