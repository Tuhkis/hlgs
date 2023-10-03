#define HL_NAME(n) hlgs_##n
#include "hl.h"

#include "gunslinger/gs.h"


static void _hlgs_init()    {}
static void _hlgs_frame()   {}
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

/* =============== CommandBuffer =============== */
#define TGSCB _ABSTRACT(hlgs_cb)

HL_PRIM gs_command_buffer_t* HL_NAME(new_command_buffer_ex) () {
  gs_command_buffer_t* ret = malloc(sizeof(gs_command_buffer_t));
  *ret = gs_command_buffer_new();
  return ret;
}

HL_PRIM void HL_NAME(dispose_command_buffer_ex) (gs_command_buffer_t* cb) {
  gs_command_buffer_free(cb);
}

HL_PRIM void HL_NAME(submit_command_buffer_ex) (gs_command_buffer_t* cb) {
  gs_graphics_command_buffer_submit(cb);
}

HL_PRIM void HL_NAME(begin_renderpass_command_buffer_ex) (gs_command_buffer_t* cb) {
  gs_graphics_renderpass_begin(cb, GS_GRAPHICS_RENDER_PASS_DEFAULT);
}

HL_PRIM void HL_NAME(end_renderpass_command_buffer_ex) (gs_command_buffer_t* cb) {
  gs_graphics_renderpass_end(cb);
}

HL_PRIM void HL_NAME(clear_command_buffer_ex) (gs_command_buffer_t* cb, float r, float g, float b) {
  gs_graphics_clear_desc_t clear = (gs_graphics_clear_desc_t) {
    .actions = &(gs_graphics_clear_action_t){.color = {r, g, b, 1.f}}
  };
  gs_graphics_clear(cb, &clear);
}
/* =============== CArrayFloat =============== */
typedef struct cArrayFloat {
  float* data;
  unsigned int len;
} CArrayFloat;
#define TCARRAYFLOAT _ABSTRACT(hlgs_carrayfloat)

HL_PRIM CArrayFloat* HL_NAME(new_carrayfloat_ex) (int len) {
  float* data = malloc(sizeof(float) * len);
  CArrayFloat* ret = malloc(sizeof(CArrayFloat));
  ret->data = data;
  return ret;
}

HL_PRIM void HL_NAME(dispose_carrayfloat_ex) (CArrayFloat* arr) {
  free(arr->data);
  free(arr);
  arr-> data = NULL;
  arr = NULL;
}

HL_PRIM void HL_NAME(carrayfloat_set_nth_ex) (CArrayFloat* arr, unsigned int n, float value) {
  if (n < arr->len && arr != NULL)
    arr->data[n] = value;
}

/* =============== VertexBuffer =============== */
#define TGSVBO _ABSTRACT(hlgs_vbo)
HL_PRIM gs_handle(gs_graphics_vertex_buffer_t)* HL_NAME(new_vbo_ex) (vbyte* data, int len_of_data) {
  float v_data[len_of_data];
  for (char i = 0; i < len_of_data; ++i) {
    printf_s("%d of data: %f\n", i, *data);
  }
  return NULL;
}

/* =============== Pipeline =============== */
#define TGSPIP _ABSTRACT(hlgs_pipeline)

/* =============== Shader =============== */
#define TGSSHADER _ABSTRACT(hlgs_shader)

/* CArrayFloat */
DEFINE_PRIM(TCARRAYFLOAT, new_carrayfloat_ex, _I32);
DEFINE_PRIM(_VOID, dispose_carrayfloat_ex, TCARRAYFLOAT);
DEFINE_PRIM(_VOID, carrayfloat_set_nth_ex, TCARRAYFLOAT _I32 _F32);
/* CommandBuffer */
DEFINE_PRIM(_VOID, clear_command_buffer_ex, TGSCB _F32 _F32 _F32);
DEFINE_PRIM(_VOID, end_renderpass_command_buffer_ex, TGSCB);
DEFINE_PRIM(_VOID, begin_renderpass_command_buffer_ex, TGSCB);
DEFINE_PRIM(_VOID, dispose_command_buffer_ex, TGSCB);
DEFINE_PRIM(_VOID, submit_command_buffer_ex, TGSCB);
DEFINE_PRIM(TGSCB, new_command_buffer_ex, _NO_ARG);
/* VertexBuffer */
DEFINE_PRIM(TGSVBO, new_vbo_ex, _BYTES _I32);
/* Misc */
DEFINE_PRIM(_VOID, create_ex, _DYN _BYTES _I32);
DEFINE_PRIM(_BOOL, app_is_running, _NO_ARG);
DEFINE_PRIM(_VOID, frame, _NO_ARG);

