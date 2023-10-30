#define HL_NAME(n) hlgs_##n
#include "hl.h"

#include "gunslinger/gs.h"


static void _hlgs_init()    {}
static void _hlgs_frame()   {}
static void _hlgs_cleanup() {}

static inline void chars_from_vbytes(char* dst, vbyte* str, int len) {
  for (int i = 0; i < len; ++i)
    dst[i] = *(str + i * 2);
}

HL_PRIM void HL_NAME(create_ex) (vdynamic* app, vbyte* title, int title_len) {
  gs_app_desc_t a;
  a.window.width = hl_dyn_geti(app, hl_hash_utf8("width"), &hlt_i32);
  a.window.height = hl_dyn_geti(app, hl_hash_utf8("height"), &hlt_i32);

  char title_buf[title_len + 1];
  title_buf[title_len] = 0;
  chars_from_vbytes(title_buf, title, title_len);

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

HL_PRIM void HL_NAME(draw_command_buffer_ex) (gs_command_buffer_t* cb, int start, int end) {
  gs_graphics_draw(cb, &(gs_graphics_draw_desc_t){.start = start, .count = end});
}

HL_PRIM void HL_NAME(apply_vbo_command_buffer_ex) (gs_command_buffer_t* cb, gs_handle(gs_graphics_vertex_buffer_t)* vbo) {
  gs_graphics_bind_desc_t binds = (gs_graphics_bind_desc_t) {
    .vertex_buffers = {&(gs_graphics_bind_vertex_buffer_desc_t) {.buffer = *vbo}},
  };
  gs_graphics_apply_bindings(cb, &binds);
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
  ret->len = len;
  return ret;
}

HL_PRIM void HL_NAME(dispose_carrayfloat_ex) (CArrayFloat* arr) {
  free(arr->data);
  free(arr);
}

HL_PRIM void HL_NAME(carrayfloat_set_nth_ex) (CArrayFloat* arr, unsigned int n, float value) {
  if (n < arr->len && arr != NULL)
    arr->data[n] = value;
}

/* =============== VertexBuffer =============== */
#define TGSVBO _ABSTRACT(hlgs_vbo)
HL_PRIM gs_handle(gs_graphics_vertex_buffer_t)* HL_NAME(new_vbo_ex) (CArrayFloat* d) {
  gs_handle(gs_graphics_vertex_buffer_t)* ret = malloc(sizeof(gs_graphics_vertex_buffer_desc_t));
  *ret = gs_graphics_vertex_buffer_create(&(gs_graphics_vertex_buffer_desc_t) {
    .data = d->data,
    .size = sizeof(float) * (d->len),
  });
  return ret;
}

HL_PRIM void HL_NAME(dispose_vbo_ex) (gs_handle(gs_graphics_vertex_buffer_t)* vbo) {
  free(vbo);
}

/* =============== Shader =============== */
#define TGSSHADER _ABSTRACT(hlgs_shader)
HL_PRIM gs_handle(gs_graphics_shader_t)* HL_NAME(new_shader_ex) (vbyte* v_src, int v_len, vbyte* f_src, int f_len, vbyte* name, int name_len) {
  char vertex[v_len + 1];
  vertex[v_len] = 0;
  chars_from_vbytes(vertex, v_src, v_len);

  char fragment[f_len + 1];
  fragment[f_len] = 0;
  chars_from_vbytes(fragment, f_src, f_len);

  char title[64];
  for (int i = 0; i < 64; ++i) title[i] = '\0';
  chars_from_vbytes(title, name, name_len);
  
  gs_handle(gs_graphics_shader_t)* ret = malloc(sizeof(gs_handle(gs_graphics_shader_t)));
  *ret = gs_graphics_shader_create(&(gs_graphics_shader_desc_t) {
    .sources = (gs_graphics_shader_source_desc_t[]) {
      {.type = GS_GRAPHICS_SHADER_STAGE_VERTEX, .source = vertex},
      {.type = GS_GRAPHICS_SHADER_STAGE_FRAGMENT, .source = fragment}
    },
    .size = 2 * sizeof(gs_graphics_shader_source_desc_t),
    .name = title
  });
  return ret;
}

HL_PRIM void HL_NAME(dispose_shader_ex) (gs_handle(gs_graphics_shader_t)* shader) {
  free(shader);
}

/* =============== Pipeline =============== */
#define TGSPIP _ABSTRACT(hlgs_pipeline)
HL_PRIM gs_handle(gs_graphics_pipeline_t)* HL_NAME(new_pipeline_ex) (gs_handle(gs_graphics_shader_t)* shader) {
  gs_handle(gs_graphics_pipeline_t)* ret = malloc(sizeof(gs_handle(gs_graphics_pipeline_t)));
  *ret = gs_graphics_pipeline_create(&(gs_graphics_pipeline_desc_t) {
    .raster = { .shader = *shader },
    .layout = {
      .attrs = (gs_graphics_vertex_attribute_desc_t[]) {
        {.format = GS_GRAPHICS_VERTEX_ATTRIBUTE_FLOAT2, .name = "a_pos"},
      },
      .size = sizeof(gs_graphics_vertex_attribute_desc_t)
    }
  });
  return ret;
}

HL_PRIM void HL_NAME(dispose_pipeline_ex) (gs_handle(gs_graphics_pipeline_t)* pip) {
  free(pip);
}

HL_PRIM void HL_NAME(bind_pipeline_ex) (gs_handle(gs_graphics_pipeline_t)* pip, gs_command_buffer_t* cb) {
  gs_graphics_pipeline_bind(cb, *pip);
}

/* Pipeline */
DEFINE_PRIM(TGSPIP, new_pipeline_ex, TGSSHADER);
DEFINE_PRIM(_VOID, dispose_pipeline_ex, TGSPIP);
DEFINE_PRIM(_VOID, bind_pipeline_ex, TGSPIP TGSCB);
/* Shader */
DEFINE_PRIM(TGSSHADER, new_shader_ex, _BYTES _I32 _BYTES _I32 _BYTES _I32);
DEFINE_PRIM(_VOID, dispose_shader_ex, TGSSHADER);
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
DEFINE_PRIM(_VOID, draw_command_buffer_ex, TGSCB _I32 _I32);
DEFINE_PRIM(_VOID, apply_vbo_command_buffer_ex, TGSCB TGSVBO);
/* VertexBuffer */
DEFINE_PRIM(TGSVBO, new_vbo_ex, TCARRAYFLOAT);
DEFINE_PRIM(_VOID, dispose_vbo_ex, TGSVBO);
/* Misc */
DEFINE_PRIM(_VOID, create_ex, _DYN _BYTES _I32);
DEFINE_PRIM(_BOOL, app_is_running, _NO_ARG);
DEFINE_PRIM(_VOID, frame, _NO_ARG);
