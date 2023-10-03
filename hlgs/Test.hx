package hlgs;

class Test {
  public static function main() {
    var app: AppDesc = new AppDesc();
    var cb: CommandBuffer;

    Gs.create(app);

    cb = new CommandBuffer();

    var shader = new Shader(
      "#version 330 core
      precision mediump float;
      layout(location = 0) in vec2 a_pos;
      void main() {
        gl_Position = vec4(a_pos, 0.0, 1.0);
      }",
      
      "#version 330 core
      precision mediump float;
      out vec4 frag_color;
      void main() {
        frag_color = vec4(1.0, 0.34, 0.2, 1.0);
      }",
      
      "Triangle");

    var pip: Pipeline = new Pipeline(shader);

    var vertexData: Array<Single> = [
       0.0,  0.5,
      -0.5, -0.5,
       0.5, -0.5
    ];
    var vbo: VertexBuffer = VertexBuffer.fromArray(vertexData);

    while (Gs.appIsRunning()) {
      cb.renderpassBegin();
        cb.clear(0.2, 0.2, 0.2);
        cb.bindPipeline(pip);
        cb.applyVbo(vbo);
        cb.draw(0, 3);
      cb.renderpassEnd();
      cb.submit();
      Gs.frame();
    }
    vbo.dispose();
    pip.dispose();
    cb.dispose();
    trace('All works!');
  }
}

